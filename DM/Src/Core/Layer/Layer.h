#pragma once
#include<Core/EventSystem/Event/Event.h>
namespace DM
{
	class DM_API Layer
	{
	public:
		Layer() = default;
		virtual ~Layer() = default;
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(const Event*const e) {}
	};
}

