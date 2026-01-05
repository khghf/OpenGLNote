#pragma once
#include<Core/Layer/Layer.h>
struct ImGuiIO;
struct GLFWwindow;
namespace DM
{
	class  ImGuiLayer:public Layer
	{
	public:
		ImGuiLayer(std::string_view name);
		virtual ~ImGuiLayer();
		virtual void OnAttach()override;
		virtual void OnDetach()override;
		virtual void OnEvent(Event* const e) override;
		virtual void OnUpdate(float DeltaTime)override;
		bool BlockEvent(bool bIsBlock) { m_bBlockEvent = bIsBlock; return m_bBlockEvent; }
	protected:
		void Begin()override;
		virtual void Render()override;
		void End()override;
	private:
		bool m_bBlockEvent = false;
	};
}


