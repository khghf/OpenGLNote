#pragma once
#include"DM.h"
#include<FrameWork/GWorld.h>
namespace DM
{
	class Panel
	{
		friend class EditorLayer;
	public:
		
		virtual ~Panel() = default;
	protected:
		void SetContext(const Ref<GWorld>& context) { m_Context = context; }
		virtual void Render() = 0;
	protected:
		Ref<GWorld>m_Context;
	};
}