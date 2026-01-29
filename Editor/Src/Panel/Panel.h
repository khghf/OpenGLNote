#pragma once
#include"DM.h"
namespace DM
{
	class Panel
	{
		friend class EditorLayer;
	public:
		using Context = GWorld;
		virtual ~Panel() = default;
	protected:
		void SetContext(const Ref<Context>& context) { m_Context = context; }
		virtual void Render() = 0;
	protected:
		Ref<Context>m_Context;
	};
}