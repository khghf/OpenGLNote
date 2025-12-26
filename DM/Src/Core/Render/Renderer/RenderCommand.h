#pragma once
#include"RendererAPI.h"
#include<Core/Math/Vector.h>
namespace DM
{
	class VertexArray;
	class RendererAPI;
	class RenderCommand
	{
	public:
		inline static void Init() { s_API->Init(); }
		inline static void SetClearColor(const Vector4& color) { s_API->SetClearColor(color); }
		inline static void Clear() { s_API->Clear(); }
		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { s_API->DrawIndexed(vertexArray); }
	private:
		static RendererAPI*s_API;
	};
}