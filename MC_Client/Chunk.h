#pragma once
#include"GShape.h"
#include<vector>
class Shader;
class VertexArray;
class Texture2D;
class Chunk:public GShape
{
public:
	Chunk();
private:
	std::vector<float>Vertices = {
		-0.5f,	0.5f,	0.f,//左上	
		 0.f,1.f,
		 0.5f,	0.5f,	0.f,//右上
		 1.f,1.f,
		-0.5f, -0.5f,	0.f,//左下
		 0.f,0.f,
		 0.5f, -0.5f,	0.f,//右下
		 1.f,0.f
	};
	std::vector<unsigned int>Indices = {
		0,1,2,
		1,2,3
	};
	SPtr<VertexArray>VAO;
	SPtr<Shader>shader;
	SPtr<Texture2D>DiffuseTex;
	SPtr<Texture2D>SpecularTex;
public:
	void Render();
public:
	virtual void Start()override;
	virtual void Update(float DeltaTime)override;
private:
	virtual void OnDestroy() override;
};