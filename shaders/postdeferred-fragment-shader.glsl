#version 330

smooth in vec2 UV;

out vec3 COLOUR;

uniform mat4 PERSPECTIVE_MATRIX;
uniform mat4 CAMERA_MATRIX;

uniform sampler2D POSITION_BUFFER;
uniform sampler2D NORMAL_BUFFER;
uniform sampler2D COLOUR_BUFFER;

const int LIGHT_NUMBER = 32;
uniform lowp vec4 LIGHT_VECTOR[LIGHT_NUMBER];
uniform lowp vec4 LIGHT_COLOUR[LIGHT_NUMBER];

vec4 BUFFER_POSITION;
vec4 BUFFER_NORMAL;
vec3 BUFFER_COLOUR;

float getSpecular(vec4 vector)
{
	lowp float specular_shininess = 5.0;//MATERIAL_DATA[0];
	lowp float specular_amount = 0.3;//MATERIAL_DATA[1];
	lowp float specular_cap = 2.0;//MATERIAL_DATA[2];

	vec4 cam_normal = CAMERA_MATRIX * BUFFER_NORMAL;

	lowp vec3 N = normalize((cam_normal).xyz);
	lowp vec3 L = normalize((CAMERA_MATRIX * vector).xyz);
	lowp vec3 R = normalize(2.0 * N * dot(N, L) - L);
	lowp vec3 V = normalize((CAMERA_MATRIX * BUFFER_POSITION).xyz / 2.0);

	lowp float specular = (dot(R, V) - (1.0 - specular_amount)) * 1.0 / specular_amount;
	specular = min(specular_cap, pow(max(0.0, specular), max(0.00001, specular_shininess)) * specular_shininess * 0.2);
	return specular;
}

float getDiffuse(vec4 vector, float ambiance)
{
	return min(1.0, max(ambiance, dot(normalize(BUFFER_NORMAL).xyz, -normalize(vector.xyz))));
}

vec4 getVector(vec4 vector)
{
	if (vector.w == 1.0) //It's a point light
		return normalize(vec4((BUFFER_POSITION).xyz - vector.xyz, 0.0));
	else //It's a directional light
		return normalize(vector);
}

void main()
{
	//Initialise the specular and diffuse
	lowp vec3 specular = vec3(0.0, 0.0, 0.0);
	lowp vec3 diffuse  = vec3(0.0, 0.0, 0.0);
	vec2 pos = (vec2(1.0, 1.0) + UV) / 2.0;

	//pos += 0.15 * vec2(getPerlin(vec4(UV / 6.0, 0.0, 0.0), 1.0, 3.0, 1.0), getPerlin(vec4(UV / 6.0, 0.0, 1.0), 1.0, 3.0, 1.0));

	BUFFER_POSITION = vec4(texture(POSITION_BUFFER, pos).rgb, 1.0);
	BUFFER_NORMAL = vec4(texture(NORMAL_BUFFER, pos).rgb, 0.0);
	BUFFER_COLOUR = texture(COLOUR_BUFFER, pos).rgb;

	//Loop through all the lights
	for (int count = 0; count < 16; count ++)
	{
		//Find the direction and colour of each light
		vec4 vector = getVector(LIGHT_VECTOR[count]);
		vec4 colour = LIGHT_COLOUR[count];

		if (colour.xyz != vec3(0.0, 0.0, 0.0)) //If the light is actually a light
		{
			float multiplier = 1.0;

			if (vector.w == 1.0) //Decrease brightness with distance
			{
				multiplier = min(1.0, 5.0 / pow(distance((BUFFER_POSITION).xyz, LIGHT_VECTOR[count].xyz), 1.5));

				//Spotlight - WIP
				//multiplier *= pow(1.05 * dot(normalize(vec3(1.0, 0.9, -2.5)), vector.xyz), 5.0);
			}

			//Add the light to the existing lighting conditions
			specular += colour.xyz * getSpecular(vector) * multiplier; //Find the specular component
			diffuse  += colour.xyz * getDiffuse(vector, colour.w) * multiplier; //Find the diffuse component
		}
	}

	COLOUR = BUFFER_COLOUR * diffuse + specular;

	for (float x = -1.0; x < 1.0; x += 1.0)
	{
		for (float y = -1.0; y < 1.0; y += 1.0)
		{
			float dist = length(texture(POSITION_BUFFER, pos + vec2(x, y) * 0.005).rgb - BUFFER_POSITION.xyz);

			if (dist > 0.3)
				COLOUR *= 0.7;
		}
	}

	COLOUR = floor(COLOUR * 8.0) / 8.0;

	//Faded corners
	COLOUR *= mix(vec3(0.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0), min(1, 1.5 - length(UV)));
}
