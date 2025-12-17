#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
struct Material
{
	sampler2D DiffuseTex;
	sampler2D SpecularTex;

};
uniform Material material;
void main()
{
	FragColor=texture(material.DiffuseTex, TexCoord)+texture(material.SpecularTex, TexCoord);
	// FragColor=vec4(1.0,0.0,0.0,1.0);
}