#version 330 core

//----UNIFORMS----
uniform            mat4 PERSPECTIVE_MATRIX;
uniform            mat4 CAMERA_MATRIX;
uniform            mat4 MODEL_MATRIX;

//----INPUTS----
in         highp   vec3 VERTEX_POS;
in         lowp    vec3 VERTEX_COL;
in         mediump vec2 VERTEX_UV;
in         lowp    vec3 VERTEX_NORM;

//----OUTPUTS----
smooth out highp   vec4 F_W_POSITION;
smooth out lowp    vec3 F_W_COLOUR;
smooth out mediump vec2 F_W_UV;
smooth out lowp    vec4 F_W_NORMAL;
smooth out highp   vec4 F_M_POSITION;
smooth out lowp    vec4 F_M_NORMAL;

void main()
{
	gl_Position  = PERSPECTIVE_MATRIX * CAMERA_MATRIX * MODEL_MATRIX * vec4(VERTEX_POS, 1.0);

	F_W_POSITION = MODEL_MATRIX * vec4(VERTEX_POS, 1.0);
	F_M_POSITION = vec4(VERTEX_POS, 1.0);

	F_W_NORMAL   = MODEL_MATRIX * normalize(vec4(VERTEX_NORM, 0.0));
	F_M_NORMAL   = normalize(vec4(VERTEX_NORM, 0.0));

	F_W_COLOUR   = VERTEX_COL;
	F_W_UV       = VERTEX_UV;
}
