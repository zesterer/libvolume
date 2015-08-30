#version 330 core

//----UNIFORMS----
uniform   highp   uint      TICK;

uniform   lowp    mat4      PERSPECTIVE_MATRIX;
uniform   lowp    mat4      CAMERA_MATRIX;
uniform   lowp    mat4      MODEL_MATRIX;

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
layout (location = 0) out vec3 POSITION_BUFFER;
layout (location = 1) out vec3 NORMAL_BUFFER;
layout (location = 2) out vec4 COLOUR_BUFFER;
layout (location = 3) out highp float DEPTH_BUFFER;

vec3 getTexture()
{
	return mix(vec3(0.7, 0.35, 0.05), vec3(0.0, 1.0, 0.0), dot((normalize(MODEL_MATRIX * F_W_NORMAL)).xyz, vec3(0.0, 0.0, 1.0)));

	/*//No proper texture has been loaded in, so revert to colours
	if (textureSize(TEXTURE_SAMPLER, 0) == ivec2(1, 1))
		return FRAG_COL;

	if (F_W_UV == vec2(-1.0, -1.0)) //If there's no texture
		return FRAG_COL;
	else //It's got a texture!
		return FRAG_COL * texture2DProjLod(TEXTURE_SAMPLER, vec3(F_W_UV, 1.0), 0.0).rgb;*/
}

void main()
{
	POSITION_BUFFER = F_W_POSITION.xyz;
	NORMAL_BUFFER = F_W_NORMAL.xyz;
	COLOUR_BUFFER.rgb = getTexture();
	DEPTH_BUFFER = 1.0;//length((CAMERA_MATRIX * F_W_POSITION).xyz);
}
