#pragma once
#include"../VertexArray.h"
#include<Core/Core.h>
#include<Core/Math/Vector.h>
namespace DM
{
	class VertexArray;
	//对不同平台的底层渲染API的抽象
	class RendererAPI
	{
	public:
		enum class EAPI
		{
			None,
			OpenGl,
		};
	public:
		virtual void Init() = 0;
		virtual void SetClearColor(const Vector4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const Ref<VertexArray>&vertexArray) = 0;
		inline static EAPI GetAPI(){ return s_API; }
	private:
		static EAPI s_API;
	};
}