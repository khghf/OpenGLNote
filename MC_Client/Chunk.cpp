#include "Chunk.h"
#include"AssetManager.h"
#include"VertexArray.h"
#include"Shader.h"
#include"Texture2D.h"
#include<Util.h>
Chunk::Chunk()
{
	VAO = std::make_shared<VertexArray>(Vertices, Indices);
	std::vector<VertexAttribute>VAttribute = {
		VertexAttribute(0,3,VertexAttribute::Float,5*sizeof(float),0),//位置
		VertexAttribute(1,2,VertexAttribute::Float,5*sizeof(float),3*sizeof(float))//纹理坐标位置
	};
	VAO->AddVertexAttributeConfig(VAttribute);
	shader = AssetManager::GetSingletion()->GetAsset<Shader>("Chunk");
	DiffuseTex = AssetManager::GetSingletion()->GetAsset<Texture2D>("container_diffuse.png");
	SpecularTex = AssetManager::GetSingletion()->GetAsset<Texture2D>("container_specular.png");
	shader->Use(); 
	//Util::Print(DiffuseTex->GetTextureUnit());
	DiffuseTex->Bind(0);
	SpecularTex->Bind(1);
	shader->SetInt("material.DiffuseTex", DiffuseTex->GetTextureUnit());
	shader->SetInt("material.SpecularTex", SpecularTex->GetTextureUnit());
	//Util::Print(DiffuseTex->GetTextureUnit());
}

void Chunk::Render()
{
	assert(VAO != nullptr&&"VAO is invalid");
	shader->Use();
	//shader->SetInt("material.DiffuseTex", DiffuseTex->GetTextureUnit());
	VAO->Render();
}

void Chunk::Start()
{
}

void Chunk::Update(float DeltaTime)
{
	Render();
}

void Chunk::OnDestroy()
{
}
