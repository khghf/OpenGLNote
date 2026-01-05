#include<DMPCH.h>
#include "GameStatic.h"
#include<fstream>
#include<sstream>
#include<filesystem>
#include<Core/Core.h>
#include<Resource/AssetManager.h>
namespace fs = std::filesystem;
namespace DM
{
	Array<std::string> GameStatic::GetAllFilePath(const std::string& FloderPath, bool GetSubFloderFile)
	{
		std::vector<std::string>FilePaths;
		fs::path Path = FloderPath;
		if (!fs::is_directory(Path) || !fs::exists(Path))
		{
			LOG_CORE_ERROR("passed a useless floder path:{}", fs::absolute(Path).string());
			return FilePaths;
		}
		for (const auto& File : fs::directory_iterator(Path))
		{
			if (File.is_regular_file())
			{
				FilePaths.push_back(File.path().string());
			}
			else
			{
				auto SubFiles = GetAllFilePath(File.path().string(), GetSubFloderFile);
				FilePaths.insert(FilePaths.end(), SubFiles.begin(), SubFiles.end());
			}
		}
		return FilePaths;
	}
	std::string GameStatic::LoadText(const std::string& Path)
	{
		std::ifstream TextFile(Path, std::ios::in|std::ios::binary);
		if (TextFile)
		{
			std::string Context = "";
			std::stringstream ss;
			ss << TextFile.rdbuf();
			TextFile.close();
			Context = ss.str();

			const char utf8_bom[] = "\xEF\xBB\xBF";
			if (Context.size() >= 3 && Context.substr(0, 3) == utf8_bom) {
				Context.erase(0, 3); // 去掉BOM头
			}

			return Context;
		}
		else
		{
			LOG_CORE_ERROR("Could not open file:{}", fs::absolute(Path).string());
		}
		return {};
	}
	std::string GameStatic::ConvertPathToName(const std::string& Path, bool bWithSuffix)
	{
		fs::path path = Path;
		return bWithSuffix ? path.filename().string() : path.stem().string();
	}
	std::string GameStatic::GetSuffix(const std::string& str)
	{
		const auto& Index = str.find_last_of('.');
		const std::string& Suffix = str.substr(Index + 1);
		return Suffix;
	}
	Ref<Shader> GameStatic::GetShader(const std::string& name)
	{
		return AssetManager::GetInst()->GetAsset<Shader>(name);
	}
	Ref<Texture2D> GameStatic::GetTexture2D(const std::string& name)
	{
		return AssetManager::GetInst()->GetAsset<Texture2D>(name);
	}
}


