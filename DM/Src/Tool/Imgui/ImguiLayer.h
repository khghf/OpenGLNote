#pragma once
#include<Core/Layer/Layer.h>
struct ImGuiIO;
struct GLFWwindow;
namespace DM
{
	class DM_API ImguiLayer:public Layer
	{
	public:
		ImguiLayer();
		virtual ~ImguiLayer();
		virtual void OnAttach()override;
		virtual void OnDetach()override;
		virtual void OnUpdate(float DeltaTime)override;
		//virtual void OnEvent(Event* const e)override;
	protected:
		void Begin();
		void ImGuiRender();
		void End();
		/*bool OnKeyClicked(Event* const e);
		bool OnKeyPressed(Event* const e);
		bool OnKeyRepeated(Event* const e);
		bool OnKeyReleased(Event* const e);
		bool OnKeyTyped(Event* const e);

		bool OnMouseClicked(Event* const e);
		bool OnMousePressed(Event* const e);
		bool OnMouseReleased(Event* const e);
		bool OnMouseMove(Event* const e);
		bool OnMouseScroll(Event* const e);

		bool OnWindowResize(Event* const e);

	protected:
		void UpdateKeyModifiers(ImGuiIO& io, GLFWwindow* window);*/
	private:
		float m_Time = 0.f;
	};
}


