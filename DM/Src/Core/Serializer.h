#pragma once
#include<Core/MMM/Reference.h>
#include<filesystem>
namespace DM
{
	class GWorld;
	class Serializer
	{
	public:
		static void Serialize(const Ref<GWorld>&scene);
		static Ref<GWorld> DeSerialize(const std::filesystem::path& filepath);
	};
}


