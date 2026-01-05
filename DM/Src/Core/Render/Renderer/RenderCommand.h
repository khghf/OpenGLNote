#pragma once
#include"RendererAPI.h"
#include<Core/Math/Vector.h>
#include<Core/MMM/Reference.h>
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
		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray,uint32_t indexElementCount=0) { s_API->DrawIndexed(vertexArray, indexElementCount); }
		inline static void SetViewport(uint32_t width, uint32_t height, uint32_t xOffset = 0, uint32_t yOffset = 0) { s_API->SetViewport(width, height,xOffset,yOffset); }
	private:
		static RendererAPI*s_API;
	};
}