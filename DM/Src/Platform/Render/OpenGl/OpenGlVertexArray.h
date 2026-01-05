#pragma once
#include<Core/Render/VertexArray.h>
#include<Core/MMM/Reference.h>
namespace DM
{
	class OpenGlVertexArray :public VertexArray
	{
	public:
		OpenGlVertexArray();
		~OpenGlVertexArray();
		virtual void Bind() override;
		virtual void UnBind()override;
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
		virtual const Array<Ref<VertexBuffer>>& GetVertexBuffer()const override { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer()const override { return m_IndexBuffer; }
	private:
		Array<Ref<VertexBuffer>>m_VertexBuffers;
		Ref<IndexBuffer>m_IndexBuffer;
		uint32_t m_Id;
	};
	
}


