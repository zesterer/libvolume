#version 330

smooth in vec2 UV;

out vec3 COLOUR;

uniform float ASPECT_RATIO;
uniform float FOV;
uniform vec3  BACKGROUND_COLOUR;
uniform float FOG_DISTANCE;

uniform int TIME;

uniform mat4 PERSPECTIVE_MATRIX;
uniform mat4 CAMERA_MATRIX;

uniform highp sampler2D POSITION_BUFFER;
uniform highp sampler2D MESH_POSITION_BUFFER;
uniform highp sampler2D NORMAL_BUFFER;
uniform highp sampler2D COLOUR_BUFFER;

const int LIGHT_NUMBER = 32;
uniform highp vec4 LIGHT_VECTOR[LIGHT_NUMBER];
uniform highp vec4 LIGHT_COLOUR[LIGHT_NUMBER];
uniform highp vec4 LIGHT_DIRECT[LIGHT_NUMBER];

highp vec4  BUFFER_POSITION;
highp vec4  BUFFER_MESH_POSITION;
highp vec4  BUFFER_NORMAL;
highp vec3  BUFFER_COLOUR;
highp float CURRENT_DEPTH;

float getSpecular(vec3 vector)
{
	lowp float specular_shininess = 2.0;//MATERIAL_DATA[0];
	lowp float specular_amount = 0.3;//MATERIAL_DATA[1];
	lowp float specular_cap = 2.0;//MATERIAL_DATA[2];

	if (false && (specular_amount < 0.01 || specular_shininess < 0.01 || specular_cap < 0.01))
		return 0.0;
	else
	{
		vec4 cam_normal = CAMERA_MATRIX * BUFFER_NORMAL;

		lowp vec3 N = cam_normal.xyz;
		lowp vec3 L = (CAMERA_MATRIX * vec4(vector, 0.0)).xyz;
		lowp vec3 R = 2.0 * N * dot(N, L) - L;
		lowp vec3 V = normalize((CAMERA_MATRIX * BUFFER_POSITION).xyz / 2.0);

		lowp float specular = max(0.0, (dot(R, V) - (1.0 - specular_amount)) * 1.0 / specular_amount);
		specular = min(specular_cap, pow(max(0.0, specular), max(0.00001, specular_shininess)) * specular_shininess * 0.2);
		return specular;
	}
}

float getDiffuse(vec4 vector, float ambiance)
{
	if (vector.w == 1.0)
		ambiance = 0.0;

	return min(1.0, max(ambiance, dot(BUFFER_NORMAL.xyz, -vector.xyz)));
}

vec4 getVector(vec4 vector)
{
	if (vector.w == 1.0) //It's a point light
		return vec4(BUFFER_POSITION.xyz - vector.xyz, 1.0);
	else //It's a directional light
		return vec4(normalize(vector.xyz), 0.0);
}

float getRandom(vec4 pos)
{
	float val = fract(sin(dot(pos, vec4(3.1415, 12.9898, 78.233, 5.327)))* 43758.5453);
	return val;
}

float getNoise(vec4 pos, float octave)
{
	pos       *= pow(2.0, octave);
	vec3 mpos  = mod(pos.xyz, 1.0);
	pos        = floor(pos);

	float c000  = getRandom(pos + vec4(0.0, 0.0, 0.0, 0.0));
	float c100  = getRandom(pos + vec4(1.0, 0.0, 0.0, 0.0));
	float c010  = getRandom(pos + vec4(0.0, 1.0, 0.0, 0.0));
	float c110  = getRandom(pos + vec4(1.0, 1.0, 0.0, 0.0));

	float c001  = getRandom(pos + vec4(0.0, 0.0, 1.0, 0.0));
	float c101  = getRandom(pos + vec4(1.0, 0.0, 1.0, 0.0));
	float c011  = getRandom(pos + vec4(0.0, 1.0, 1.0, 0.0));
	float c111  = getRandom(pos + vec4(1.0, 1.0, 1.0, 0.0));

	float eX00  = mix(c000, c100, mpos.x);
	float eX10  = mix(c010, c110, mpos.x);
	float eX01  = mix(c001, c101, mpos.x);
	float eX11  = mix(c011, c111, mpos.x);

	float fXX0  = mix(eX00, eX10, mpos.y);
	float fXX1  = mix(eX01, eX11, mpos.y);

	float value = mix(fXX0, fXX1, mpos.z);

	return 2.0 * (value - 0.5);
}

float getPerlin(vec4 pos, float initial, float octaves, float skip)
{
	float val = 0.0;

	for (float x = initial; x < initial + octaves; x += skip)
		val += getNoise(pos, x + 2.0) / pow(2.0, x - initial);

	return val;
}

float getDepth(vec2 pos)
{
	return length((CAMERA_MATRIX * texture(POSITION_BUFFER, pos)).xyz);
}

vec3 getNormal(vec2 pos)
{
	return texture(NORMAL_BUFFER, pos).xyz;
}

void main()
{
	//Initialise the specular and diffuse
	lowp vec3 specular = vec3(0.0, 0.0, 0.0);
	lowp vec3 diffuse  = vec3(0.0, 0.0, 0.0);
	vec2 pos = (vec2(1.0, 1.0) + UV) / 2.0;

	//pos += 0.15 * vec2(getPerlin(vec4(UV / 6.0, 0.0, 0.0), 1.0, 3.0, 1.0), getPerlin(vec4(UV / 6.0, 0.0, 1.0), 1.0, 3.0, 1.0));

	BUFFER_POSITION = vec4(texture(POSITION_BUFFER, pos).xyz, 1.0);
	BUFFER_MESH_POSITION = vec4(texture(MESH_POSITION_BUFFER, pos).xyz, 1.0);
	BUFFER_NORMAL = vec4(normalize(texture(NORMAL_BUFFER, pos).xyz), 0.0);
	BUFFER_COLOUR = texture(COLOUR_BUFFER, pos).rgb;

	//Decode back into HDR
	BUFFER_COLOUR = BUFFER_COLOUR / (1.0 - BUFFER_COLOUR);

	if (true)
	{
		vec4 norm = vec4(0.0, 0.0, 0.0, 0.0);
		vec3 pos  = vec3(BUFFER_MESH_POSITION * 600.0).xyz;

		norm.x    = getPerlin(vec4(pos, 1.0), 0.5, 3.0, 1.0);
		norm.y    = getPerlin(vec4(pos, 2.0), 0.5, 3.0, 1.0);
		norm.z    = getPerlin(vec4(pos, 3.0), 0.5, 3.0, 1.0);
		norm      = normalize(norm);
		BUFFER_NORMAL  = normalize(BUFFER_NORMAL + norm * 0.25);
	}

	if (BUFFER_COLOUR.r > 100.0)
		BUFFER_COLOUR.r = 0.0;

	CURRENT_DEPTH = getDepth(pos);

	//Surface roughness
	if (false)
	{
		vec4 norm = vec4(0.0, 0.0, 0.0, 0.0);
		vec3 pos  = BUFFER_POSITION.xyz;

		float lod = 6.0;

		norm.x    = getPerlin(vec4(pos / 500.0, 4.0), 0.5, lod, 1.0);
		norm.y    = getPerlin(vec4(pos / 500.0, 5.0), 0.5, lod, 1.0);
		norm.z    = getPerlin(vec4(pos / 500.0, 6.0), 0.5, lod, 1.0);
		norm      = normalize(norm);
		BUFFER_NORMAL  = normalize(BUFFER_NORMAL + norm * 0.55);
	}

	//Loop through all the lights
	for (int count = 0; count < LIGHT_NUMBER; count ++)
	{
		//Find the direction and colour of each light
		vec4 colour = LIGHT_COLOUR[count];

		if (colour.xyz != vec3(0.0, 0.0, 0.0)) //If the light is actually a light
		{
			vec4 vector = getVector(LIGHT_VECTOR[count]);

			float multiplier = 1.0;

			if (vector.w == 1.0) //Decrease brightness with distance
			{
				multiplier = min(length(colour.rgb), max(0.0, 5.0 * colour.w / pow(length(vector.xyz), 1.5)));

				//if (dot(normalize(vector.xyz), vec3(0.0, 0.0, 1.0)) < 0.9)
					//multiplier = 0.0;

				multiplier *= min(1.0, pow(10.0 * max(0.0, dot(normalize(vector.xyz), normalize(LIGHT_DIRECT[count].xyz)) - LIGHT_DIRECT[count].w), 4.0));
			}

			//Add the light to the existing lighting conditions
			specular += colour.xyz * getSpecular(normalize(vector.xyz)) * multiplier; //Find the specular component
			diffuse  += colour.xyz * getDiffuse(vec4(normalize(vector.xyz), vector.w), colour.w) * multiplier; //Find the diffuse component
		}
	}

	if (BUFFER_POSITION.xyz == vec3(0.0, 0.0, 0.0))
	{
		COLOUR = BACKGROUND_COLOUR;

		//STARHACK
		float a = 0.0;//getPerlin(inverse(CAMERA_MATRIX) * normalize(vec4(-UV.x * ASPECT_RATIO * (FOV / 1.571), -UV.y * (FOV / 1.571), 1.0, 0.0)) * 1.0, 3.0, 2.0, 2.0);

		if (a > 0.85)
		{
			COLOUR = vec3(1.0, 1.0, 1.0);
		}
	}
	else
	{
		float p = 0.8 + getPerlin(BUFFER_MESH_POSITION * 1.0, 1.0, 4.0, 1.0) / 2.5;

		COLOUR = BUFFER_COLOUR * p * diffuse + specular;
	}

	/*for (float x = -1.0; x < 1.0; x += 1.0)
	{
		for (float y = -1.0; y < 1.0; y += 1.0)
		{
			float position_diff = length(texture(POSITION_BUFFER, pos + vec2(x, y) * 0.002).rgb - BUFFER_POSITION.xyz);

			if (position_diff > 0.1 * CURRENT_DEPTH)
				COLOUR += 0.25;
		}
	}*/

	//Hacked together SSAO
	/*float totaldepth = 0.0;
	for (float x = -1.0; x < 1.0; x += 0.5)
	{
		for (float y = -1.0; y < 1.0; y += 0.5)
		{
			float diff = CURRENT_DEPTH - getDepth(pos + (CAMERA_MATRIX * BUFFER_NORMAL).xy * 0.02);
			if (diff > 100.0 || diff < 0.0)
				diff = 0.0;
			diff = diff + (50.0 * dot(-getNormal(pos + (CAMERA_MATRIX * BUFFER_NORMAL).xy * 0.02), getNormal(pos)));
			totaldepth += diff;
		}
	}
	totaldepth = 1.0 - min(max(totaldepth * 0.002, 0.0), 0.6);
	COLOUR *= totaldepth;*/

	//Add fog
	if (FOG_DISTANCE > 0.0)
		COLOUR = mix(COLOUR, BACKGROUND_COLOUR, min(1.0, pow(CURRENT_DEPTH / FOG_DISTANCE, 3.5)));

	//Push HDR back into displayable ranges
	COLOUR = COLOUR / (COLOUR + 1.0);

	//Toon effect
	//COLOUR = floor(COLOUR * 6.0) / 6.0;

	//Faded corners
	COLOUR *= mix(vec3(0.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0), min(1, 2.5 - length(UV)));
}
