#pragma once
#include <string>
#include<filesystem>
namespace DM
{
	class Config
	{
		friend class Application;
		static void Init();
	public:
		static std::string				AssetFolder();
		static std::string				AssetShader();
		static std::string				AssetTexture();
		static std::string				AssetFont();
		static std::string				AssetSave();
		static std::string				AssetIcon();




		static std::string				CacheFolder();
		static std::string				CacheShaderFolder();
	};
}


