#pragma once
#include<string>
#include<Core/Container/Array.h>
#include<Core/MMM/Reference.h>
namespace DM
{
	class Shader;
	class Texture2D;
	class GameStatic
	{
	public:
		static Array<std::string>GetAllFilePath(const std::string& FloderPath, bool GetSubFloderFile = false);
		static std::string LoadText(const std::string& Path);
		static std::string ConvertPathToName(const std::string& Path, bool bWithSuffix = false);
		static std::string GetSuffix(const std::string& str);
		static Ref<Shader> GetShader(const std::string& name);
		static Ref<Texture2D> GetTexture2D(const std::string& name);
	};
}
