#pragma once
#include<Core/Render/Renderer/RendererAPI.h>
#include<Core/Math/Vector.h>
namespace DM
{
	class OpenGlRendererAPI :public RendererAPI
	{
	public:
		virtual void Init()override;
		virtual void SetClearColor(const Vector4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}