#pragma once
#include<string>
#include<vector>
class Shader;
class GameStatic
{
public:
	static std::vector<std::string>GetAllFilePath(const std::string& FloderPath,bool GetSubFloderFile=false);
	static std::string LoadText(const std::string& Path);
	static std::string ConvertPathToName(const std::string&Path,bool bWithSuffix=true);
	static std::string GetSuffix(const std::string& str);
	static bool CheckShaderCompStatus(const Shader& shader);//检查编译是否成功
	static bool CheckProgramLinkStatus(const Shader& shader);//检查链接是否成功
};