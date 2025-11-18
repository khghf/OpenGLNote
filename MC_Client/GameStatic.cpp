#include "GameStatic.h"
#include<Shader.h>
#include<fstream>
#include<sstream>
#include<filesystem>
#include<Util.h>
namespace fs = std::filesystem;
std::vector<std::string> GameStatic::GetAllFilePath(const std::string& FloderPath, bool GetSubFloderFile)
{
	std::vector<std::string>FilePaths;
	fs::path Path= FloderPath;
	if (!fs::is_directory(Path) || !fs::exists(Path))
	{
		std::cerr << "passed a useless floder path" << std::endl;
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
			auto SubFiles=GetAllFilePath(File.path().string(), GetSubFloderFile);
			FilePaths.insert(FilePaths.end(), SubFiles.begin(), SubFiles.end());
		}
	}
	return FilePaths;
}

std::string GameStatic::LoadText(const std::string& Path)
{
	std::ifstream TextFile;
	std::string Context = "";
	try
	{
		TextFile.open(Path);
		std::stringstream ss;
		ss << TextFile.rdbuf();
		TextFile.close();
		Context = ss.str();
		return Context;
	}
	catch (std::ifstream::failure&e)
	{
		std::cerr << "ERROR:LoadText failed" << e.what() << "\nPath:" << Path << std::endl;
	}
	return Context;
}

std::string GameStatic::ConvertPathToName(const std::string& Path, bool bWithSuffix)
{
	fs::path path = Path;
	return bWithSuffix ? path.filename().string() : path.stem().string();
}

std::string GameStatic::GetSuffix(const std::string& str)
{
	const auto&Index= str.find_last_of('.');
	const std::string& Suffix = str.substr(Index + 1);
	return Suffix;
}

bool GameStatic::CheckShaderCompStatus(const Shader& shader)
{
	const unsigned int& Id = shader.GetID();
	GLint Type;
	glGetShaderiv(Id, GL_SHADER_TYPE, &Type);//查询类型
	GLint Success = GL_FALSE;
	auto PrintLog = [=]() {
		GLint LogLength = 0;
		glGetShaderiv(Id, GL_INFO_LOG_LENGTH, &LogLength);
		char* InfoLog = new char[LogLength + 1];
		glGetShaderInfoLog(Id, LogLength, NULL, InfoLog);
		InfoLog[LogLength] = '\0';
		Util::Print("***********************************");
		std::cerr << "ERROR:shader "<<shader.GetName()<<" compile failed\nInfoLog:" << InfoLog << std::endl;
		Util::Print("***********************************");
		delete[] InfoLog;
		};
	if (Type == GL_VERTEX_SHADER)
	{
		glGetShaderiv(Id, GL_COMPILE_STATUS, &Success);//获取编译状态
		if (Success == GL_FALSE)
		{
			PrintLog();
			return false;
		}
	}
	else if (Type == GL_FRAGMENT_SHADER)
	{
		glGetShaderiv(Id, GL_COMPILE_STATUS, &Success);//获取编译状态
		if (Success == GL_FALSE)
		{
			PrintLog();
			return false;
		}
	}
	else
	{
		std::cerr << "UnKnow Shader Type" << std::endl;
		PrintLog();
		return false;
	}
	return true;
}

bool GameStatic::CheckProgramLinkStatus(const Shader& shader)
{
	const unsigned int& Id = shader.GetID();
	GLint Success=GL_FALSE;
	glGetProgramiv(Id, GL_LINK_STATUS, &Success);
	if (Success== GL_FALSE)
	{
		GLint LogLength = 0;
		glGetProgramiv(Id, GL_INFO_LOG_LENGTH, &LogLength);
		char* InfoLog = new char[LogLength + 1];
		glGetProgramInfoLog(Id, LogLength, NULL, InfoLog);
		InfoLog[LogLength] = '\0';
		std::cerr << "ERROR:program "<< shader.GetName()<< " link failed\nInfoLog:" << InfoLog << std::endl;
		delete[] InfoLog;
		GLint attached;
		glGetProgramiv(Id, GL_ATTACHED_SHADERS, &attached);
		std::cout << "附加后着色器数量：" << attached << std::endl;
		return false;
	}
	return true;
}

