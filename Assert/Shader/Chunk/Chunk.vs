#version 450 core
layout(location=0) in vec3 a_Pos;
layout(location=1) in vec2 a_TexCoord;
uniform mat4 u_ProjectionViewMatrix;
uniform mat4 u_ModelMatrix;
out vec2 v_TexCoord;
void main()
{
	v_TexCoord=a_TexCoord;
	gl_Position = u_ProjectionViewMatrix*u_ModelMatrix*vec4(a_Pos, 1.0);
}