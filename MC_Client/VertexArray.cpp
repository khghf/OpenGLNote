#include "VertexArray.h"
#include"Util.h"
VertexArray::VertexArray()
{
	glGenVertexArrays(1, &Id);
}



void VertexArray::Render(GLenum DrawMode)
{
	if (IBO)
	{
		RenderIndex(DrawMode);
		//Util::Print("RenderIndex");
	}
	else
	{
		RenderVertex(DrawMode);
	}
}

void VertexArray::RenderVertex(GLenum DrawMode)
{
	assert(VBO != nullptr&&"VertexArray：VBO is invalid");
	Bind();
	glDrawArrays(DrawMode, 0, VBO->GetBufferDateSize());
}

void VertexArray::RenderIndex(GLenum DrawMode)
{
	assert(IBO != nullptr&&"VertexArray：IBO is invalid");
	//Util::Print(IBO->GetBufferDateSize());
	Bind();
	glDrawElements(DrawMode, IBO->GetBufferDateSize(), GL_UNSIGNED_INT, 0);
}

void VertexArray::AddVertexAttributeConfig(const std::vector<VertexAttribute>& Attributes)
{
	Bind();
	for (int i = 0; i < Attributes.size(); ++i)
	{
		const auto& [Location,Type,ComponentCount,bNormalized, Stride,Offset]=Attributes[i];
		const auto Nor = bNormalized ? GL_TRUE : GL_FALSE;
		switch (Type)
		{
		case VertexAttribute::UShort:
		case VertexAttribute::Int:
		case VertexAttribute::UInt:
		case VertexAttribute::Byte:
			//配置整数型顶点属性，数据以原始整数形式传递给着色器（不转换为浮点），适用于需要保留整数原值的场景
			glVertexAttribIPointer(Location, ComponentCount, Type, Stride, reinterpret_cast<void*>(Offset));
			break;
		case VertexAttribute::Float:
			//配置浮点型顶点属性,告诉 OpenGL 如何从 VBO 中读取数据
			glVertexAttribPointer(Location, ComponentCount, Type, Nor, Stride, reinterpret_cast<void*>(Offset));
			break;
		default:
			break; 
		}
		glEnableVertexAttribArray(Location); //启用状态会被当前绑定的 VAO 记录，绑定 VAO 时会自动恢复启用状态。
	}
	UnBind();
}
