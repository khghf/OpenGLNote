#pragma once
#include<Core/EventSystem/Event/Event.h>
namespace DM
{
	class DM_API Layer
	{
	public:
		Layer(std::string_view name);
		virtual ~Layer();
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float DeltaTime) {}
		virtual void OnEvent(Event*const e) {}
	private:
		std::string_view Name;
	};
}

