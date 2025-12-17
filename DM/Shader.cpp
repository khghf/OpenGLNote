#include "Shader.h"
#include<glad/glad.h>
#include<GameStatic.h>
#include<Util.h>
Shader::Shader(const std::string& Path)
{
	std::string Name = GameStatic::ConvertPathToName(Path);
	this->Name = Name;
	auto index = Name.find_last_of('.');
	std::string Suffix = Name.substr(index + 1);
	Name = Name.substr(0, index);
	EShaderType Type = EShaderType::None;
	if (Suffix == "vs")
	{
		Type = EShaderType::VS;
	}
	else if (Suffix == "fs")
	{
		Type = EShaderType::FS;
	}
	else
	{
		Util::Print("Invalid shader file");
	}
	const std::string Code = GameStatic::LoadText(Path);
	CreateShader(Code, Type);
	this->Type = Type;
}
Shader::Shader(const std::string& Code, const EShaderType& Type)
{
	this->Type = Type;
	CreateShader(Code, Type);
}
//Shader::Shader(const std::string& VSCode, const std::string& FSCode)
//{
//	auto VID=CreateShader(VSCode, EShaderType::VS);
//	auto FID=CreateShader(FSCode, EShaderType::FS);
//	CreateProgram(VID, FID);
//	this->Type = EShaderType::PS;
//}

Shader::Shader(const unsigned int& VSID, const unsigned int& FSID, const std::string& Name)
{
	this->Name = Name;
	CreateProgram(VSID, FSID);
}

unsigned int Shader::CreateShader(const std::string& Code, const EShaderType& Type)
{
	unsigned int ID = 0;
	GLenum type= GL_VERTEX_SHADER;
	if (Type == EShaderType::VS)type = GL_VERTEX_SHADER;
	else if (Type == EShaderType::FS)type = GL_FRAGMENT_SHADER;
	ID = glCreateShader(type);
	const char* Code_cstr = Code.c_str();
	glShaderSource(ID, 1, &Code_cstr, NULL);
	glCompileShader(ID);
	this->ID=ID;
	const bool& Success = GameStatic::CheckShaderCompStatus(*this);
	if (!Success)
	{
		Util::Print("***********************************");
		Util::Print("Compile failed.Source Code:\n", Code);
		Util::Print("***********************************");
	}
	return ID;
}

unsigned int Shader::CreateProgram(const unsigned int& VsId, const unsigned int& FsId)
{
	const unsigned int PID = glCreateProgram();
	glAttachShader(PID, VsId);
	glAttachShader(PID, FsId);
	glLinkProgram(PID);
	this->ID = PID;
	glDeleteShader(VsId);
	glDeleteShader(FsId);
	GameStatic::CheckProgramLinkStatus(*this);
	return PID;
}
