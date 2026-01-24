#pragma once
#include<Core/MMM/Reference.h>
#include<filesystem>
namespace DM
{
	class Scene;
	class SceneSerializer
	{
	public:
		static void Serialize(const Ref<Scene>&scene);
		static Ref<Scene> DeSerialize(const std::filesystem::path& filepath);
	};
}


