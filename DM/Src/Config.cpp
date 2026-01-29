#include "DMPCH.h"
#include "Config.h"
#include <json/json.hpp>
#include<string_view>
#include<fstream>
#include"Tool/Util/Util.h"
namespace DM
{
	static std::string_view ConfigFilePath = "../Config.json";//配置文件相对路径，配置文件由此加载并影响后面路径的值
	static std::string ConfigFilePathAbs = "";//配置文件绝对路径
	static std::string ConfigFolderPathAbs = "";//配置文件所属文件夹的绝对路径
	static nlohmann::json js;
	void Config::Init()
	{
		std::ifstream ConfigFile;
		ConfigFile.open(ConfigFilePath);
		ConfigFile >> js;
		ConfigFile.close();
		std::filesystem::path p = std::filesystem::absolute({ ConfigFilePath });
		ConfigFilePathAbs = std::filesystem::canonical(p).string();
		ConfigFolderPathAbs = std::filesystem::canonical(p.parent_path()).string();
	}

	std::string Config::AssetFolder()
	{
		return ConfigFolderPathAbs +"/" + std::string(js["Assets"]["Folder"]);
	}

	std::string Config::AssetShader()
	{
		return ConfigFolderPathAbs + "/" + std::string(js["Assets"]["Shader"]);
	}

	std::string Config::AssetTexture()
	{
		return ConfigFolderPathAbs + "/" + std::string(js["Assets"]["Texture"]);
	}

	std::string Config::AssetFont()
	{
		return ConfigFolderPathAbs + "/" + std::string(js["Assets"]["Font"]);
	}

	std::string Config::AssetSave()
	{
		return ConfigFolderPathAbs + "/" + std::string(js["Assets"]["Save"]);
	}

	std::string Config::AssetIcon()
	{
		return ConfigFolderPathAbs + "/" + std::string(js["Assets"]["Icon"]);
	}

	std::string Config::CacheFolder()
	{
		return ConfigFolderPathAbs + "/" + std::string(js["Cache"]["Folder"]);
	}

	std::string Config::CacheShaderFolder()
	{
		return ConfigFolderPathAbs +"/" + std::string(js["Cache"]["Shader"]);
	}

}