#include<DMPCH.h>
#include "OpenGlVertexArray.h"
#include<Tool/Util/GameStatic.h>
#include<Core/Log.h>
#include<glad/glad.h>
namespace DM
{
	static GLenum ShaderDataTypeToOpenGlType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::None:		DM_CORE_ASSERT(false, "{}", "Unknown ShaderDataType!"); return 0;
			case ShaderDataType::Float:		return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;
			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2:		return GL_INT;
			case ShaderDataType::Int3:		return GL_INT;
			case ShaderDataType::Int4:		return GL_INT;
			case ShaderDataType::Mat3x3:	return GL_FLOAT;
			case ShaderDataType::Mat4x4:	return GL_FLOAT;
			case ShaderDataType::Bool:		return GL_BOOL;
		}
		DM_CORE_ASSERT(false, "{}", "Unknown ShaderDataType!");
		return 0;
	}
	OpenGlVertexArray::OpenGlVertexArray()
	{
		glGenVertexArrays(1, &m_Id);
		glBindVertexArray(m_Id);
	}
	OpenGlVertexArray::~OpenGlVertexArray()
	{
		glDeleteVertexArrays(1, &m_Id);
	}
	void OpenGlVertexArray::Bind()
	{
		glBindVertexArray(m_Id);
	}
	void OpenGlVertexArray::UnBind()
	{
		glBindVertexArray(0);
	}
	void OpenGlVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		DM_CORE_ASSERT(vertexBuffer->GetLayout().GetBufferElements().size(), "{}", "Vertex Buffer has no layout!");
		glBindVertexArray(m_Id);
		vertexBuffer->Bind();
		const auto& layout = vertexBuffer->GetLayout();
		int location = 0;
		for (const auto& Element : layout)
		{
			glVertexAttribPointer(
				location,
				Element.GetComponentCount(), 
				ShaderDataTypeToOpenGlType(Element.Type), 
				Element.bNormailzed ? GL_TRUE : GL_FALSE, 
				layout.GetStride(), 
				(void*)Element.Offset);
			glEnableVertexAttribArray(location);
			++location;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}
	void OpenGlVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_Id);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
	//VertexArray::VertexArray()
	//{
	//	glGenVertexArrays(1, &Id);
	//}
	//void VertexArray::Render(unsigned int DrawMode)
	//{
	//	if (IBO)
	//	{
	//		RenderIndex(DrawMode);
	//	}
	//	else
	//	{
	//		RenderVertex(DrawMode);
	//	}
	//}
	//void VertexArray::RenderVertex(unsigned int DrawMode)
	//{
	//	DM_CORE_ASSERT(VBO, "VertexArray：VBO is invalid");
	//	Bind();
	//	glDrawArrays(DrawMode, 0, VBO->GetBufferDateSize());
	//}
	//void VertexArray::RenderIndex(unsigned int DrawMode)
	//{
	//	DM_CORE_ASSERT(IBO, "VertexArray：VBO is invalid");
	//	Bind();
	//	glDrawElements(DrawMode, IBO->GetBufferDateSize(), GL_UNSIGNED_INT, 0);
	//}
	//void VertexArray::AddVertexAttributeConfig(const std::vector<VertexAttribute>& Attributes)
	//{
	//	Bind();
	//	for (int i = 0; i < Attributes.size(); ++i)
	//	{
	//		const auto& [Location, Type, ComponentCount, bNormalized, Stride, Offset] = Attributes[i];
	//		const auto Nor = bNormalized ? GL_TRUE : GL_FALSE;
	//		switch (Type)
	//		{
	//		case VertexAttribute::UShort:
	//		case VertexAttribute::Int:
	//		case VertexAttribute::UInt:
	//		case VertexAttribute::Byte:
	//			//配置整数型顶点属性，数据以原始整数形式传递给着色器（不转换为浮点），适用于需要保留整数原值的场景
	//			glVertexAttribIPointer(Location, ComponentCount, Type, Stride, reinterpret_cast<void*>(Offset));
	//			break;
	//		case VertexAttribute::Float:
	//			//配置浮点型顶点属性,告诉 OpenGL 如何从 VBO 中读取数据
	//			glVertexAttribPointer(Location, ComponentCount, Type, Nor, Stride, reinterpret_cast<void*>(Offset));
	//			break;
	//		default:
	//			break;
	//		}
	//		glEnableVertexAttribArray(Location); //启用状态会被当前绑定的 VAO 记录，绑定 VAO 时会自动恢复启用状态。
	//	}
	//	UnBind();
	//}
}

