#pragma once
#include<Core/EventSystem/Event/Event.h>
#include<string_view>
namespace DM
{
	class  Layer
	{
		friend class LayerStack;
	public:
		Layer(std::string_view name);
		virtual ~Layer();
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnEvent(Event* const e) {}
		virtual void OnUpdate(float DeltaTime) {}
	protected:
		virtual void Begin() {};
		virtual void Render() {};
		virtual void End() {};
		std::string_view m_name;
	};
}

