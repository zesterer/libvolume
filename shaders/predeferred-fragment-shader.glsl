#version 330 core

//----UNIFORMS----
uniform   highp   uint      TICK;

uniform   highp   mat4      PERSPECTIVE_MATRIX;
uniform   highp   mat4      CAMERA_MATRIX;
uniform   highp   mat4      MODEL_MATRIX;

uniform   highp   vec3      MESH_COLOUR;

uniform   highp   vec4      LIGHT_VECTOR[16];
uniform   highp   vec4      LIGHT_COLOUR[16];

uniform   highp   vec4      MATERIAL_DATA;
uniform           int       MATERIAL_EFFECTS;

uniform           sampler2D TEXTURE_SAMPLER;

//----INPUTS----
smooth in highp   vec4      F_W_POSITION;
smooth in highp   vec3      F_W_COLOUR;
smooth in highp   vec2      F_W_UV;
smooth in highp   vec4      F_W_NORMAL;
smooth in highp   vec4      F_M_POSITION;
smooth in highp   vec4      F_M_NORMAL;

//----OUTPUTS----
layout (location = 0) out highp vec3 POSITION_BUFFER;
layout (location = 1) out highp vec3 MESH_POSITION_BUFFER;
layout (location = 2) out highp vec3 NORMAL_BUFFER;
layout (location = 3) out highp vec3 COLOUR_BUFFER;

vec3 getTexture()
{
	return F_W_COLOUR;
	//return mix(vec3(0.7, 0.35, 0.05), vec3(0.0, 1.0, 0.0), dot((normalize(MODEL_MATRIX * F_W_NORMAL)).xyz, vec3(0.0, 0.0, 1.0)));

	//No proper texture has been loaded in, so revert to colours
	/*if (textureSize(TEXTURE_SAMPLER, 0) == ivec2(1, 1))
		return F_W_COLOUR;

	if (F_W_UV == vec2(-1.0, -1.0)) //If there's no texture
		return F_W_COLOUR;
	else //It's got a texture!
		return F_W_COLOUR * texture(TEXTURE_SAMPLER, F_W_UV).rgb;*/
}

void main()
{
	POSITION_BUFFER = F_W_POSITION.xyz;
	MESH_POSITION_BUFFER = F_M_POSITION.xyz;
	NORMAL_BUFFER = F_W_NORMAL.xyz;

	COLOUR_BUFFER = F_W_COLOUR.rgb * MESH_COLOUR;

	//if (COLOUR_BUFFER.r > 20.0)
		//COLOUR_BUFFER.rgb = vec3(0.0, 100.0, 0.0);

	//Encode HDR into displayable ranges
	COLOUR_BUFFER = COLOUR_BUFFER / (COLOUR_BUFFER + 1.0);
}
