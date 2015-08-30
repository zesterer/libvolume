#version 330

smooth in vec2 UV;

out vec3 COLOUR;

uniform sampler2D POSITION_BUFFER;
uniform sampler2D NORMAL_BUFFER;
uniform sampler2D COLOUR_BUFFER;

void main()
{
	vec2 pos = (vec2(1.0, 1.0) + UV) / 2.0;

	//pos += 0.15 * vec2(getPerlin(vec4(UV / 6.0, 0.0, 0.0), 1.0, 3.0, 1.0), getPerlin(vec4(UV / 6.0, 0.0, 1.0), 1.0, 3.0, 1.0));

	vec3 position = texture(POSITION_BUFFER, pos).rgb;
	vec3 normal = texture(NORMAL_BUFFER, pos).rgb;
	vec3 colour = texture(COLOUR_BUFFER, pos).rgb;

	COLOUR = colour;

	for (float x = -1.0; x < 1.0; x += 1.0)
	{
		for (float y = -1.0; y < 1.0; y += 1.0)
		{
			float dist = length(texture(POSITION_BUFFER, pos + vec2(x, y) * 0.005).rgb - position);

			if (dist > 1.0)
				COLOUR = vec3(0.0, 0.0, 0.0);
		}
	}

	COLOUR = floor(COLOUR * 8.0) / 8.0;

	//Faded corners
	COLOUR *= mix(vec3(0.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0), min(1, 1.5 - length(UV)));
}
