#pragma once
#include "Panel.h"
#include <filesystem>
namespace DM
{
	class ContentBrowserPanel:public Panel
	{
		friend class EditorLayer;
		ContentBrowserPanel(const Ref<Context>& context);
	protected:
		virtual void Render() override;
		std::filesystem::path CurPath;
	};
}
