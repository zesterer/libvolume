#version 330 core

//----UNIFORMS----
uniform   highp   uint      TICK;

uniform   lowp    mat4      PERSPECTIVE_MATRIX;
uniform   lowp    mat4      CAMERA_MATRIX;
uniform   lowp    mat4      MODEL_MATRIX;

uniform   lowp    vec3      MESH_COLOUR;

uniform   lowp    vec4      LIGHT_VECTOR[16];
uniform   lowp    vec4      LIGHT_COLOUR[16];

uniform   lowp    vec4      MATERIAL_DATA;
uniform           int       MATERIAL_EFFECTS;

uniform           sampler2D TEXTURE_SAMPLER;

//----INPUTS----
smooth in highp   vec4      F_W_POSITION;
smooth in lowp    vec3      F_W_COLOUR;
smooth in mediump vec2      F_W_UV;
smooth in lowp    vec4      F_W_NORMAL;
smooth in highp   vec4      F_M_MODEL_POSITION;
smooth in lowp    vec4      F_M_MODEL_NORMAL;

//----OUTPUTS----
layout (location = 0) out highp vec4 POSITION_BUFFER;
layout (location = 1) out lowp vec3 NORMAL_BUFFER;
layout (location = 2) out lowp vec4 COLOUR_BUFFER;

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
	POSITION_BUFFER = F_W_POSITION;
	NORMAL_BUFFER = F_W_NORMAL.xyz;

	if (F_W_COLOUR != vec3(1.0, 1.0, 1.0))
		COLOUR_BUFFER.rgb = F_W_COLOUR.rgb;
	else
		COLOUR_BUFFER.rgb = MESH_COLOUR;
}
