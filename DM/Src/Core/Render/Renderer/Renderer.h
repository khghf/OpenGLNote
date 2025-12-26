#pragma once
#include<Core/Render/Camera/OrthoGraphicCamera.h>
#include"../Shader.h"
#include"RenderCommand.h"
namespace DM
{
	class OrthoGraphicCamera;
	class RendererAPI;
	class Renderer
	{
	public:
		static void Init();
		static void BeginScene(const Ref<OrthoGraphicCamera>& orthoCamera);
		static void EndScene();
		static void Submit(const Ref<Shader>& shader,const Ref<VertexArray>& vertexArray);
		static RendererAPI::EAPI GetAPI();
	private:
		struct SceneData
		{
			Matrix4 ProjectionViewMartix= Matrix4(1.f);
			Matrix4 ModelMartix = Matrix4(1.f);
		};
		static SceneData* m_SceneData;
	};
}