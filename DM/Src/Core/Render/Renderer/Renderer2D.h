#pragma once
#include<Core/MMM/Reference.h>
#include"../Shader.h"
#include"../Camera/OrthoGraphicCamera.h"
#include"RenderCommand.h"
#include<FrameWork/GComponent.h>
namespace DM
{
	class Texture2D;
	class Renderer2D
	{
	public:
		static void Init();
		static void ShoutDown();
		static void BeginScene(const Matrix4& projectionView);
		static void BeginScene(const Ref<Camera>& orthoCamera);
		static void EndScene();
		static void Flush();

		static void DrawQuad(const Vector2& pos, const Vector2& size, const Vector4& color);
		static void DrawQuad(const Vector3& pos, const Vector2& size, const Vector4& color);
		static void DrawQuad(const Vector2& pos, const Vector2& size, const Ref<Texture2D>& texture, const Vector2& uvTiling= Vector2(1.f,1.f), const Vector4& color = Vector4(1.f, 1.f, 1.f, 1.f));
		static void DrawQuad(const Vector3& pos, const Vector2& size, const Ref<Texture2D>& texture, const Vector2& uvTiling = Vector2(1.f, 1.f), const Vector4& color = Vector4(1.f, 1.f, 1.f, 1.f));
		

		static void DrawQuad(const SpriteComponent&sprite,const TransformComponent&transform,const Vector2& uvTiling = Vector2(1.f, 1.f));

		static RendererAPI::EAPI GetAPI();


		struct Statistics
		{
			uint32_t DrawCall = 0;
			uint32_t QuadCount = 0;
			uint32_t GetVertexCount()const { return QuadCount * 4; }
			uint32_t GetIndexCount()const { return QuadCount * 6; }
		};
		static Statistics GetStats();
		static void ResetStats();
	private:
		static void FlushAndRest();
	};
}
