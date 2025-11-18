#pragma once
#include<iostream>
#include<string>
#include"DataType.h"
#include"Asset.h"
#include"Util.h"
class Shader:public Asset
{
public:
	Shader(const std::string& Path);
	Shader(const std::string& Code,const EShaderType&Type);
	Shader(const unsigned int& VSID, const unsigned int& FSID,const std::string&Name);
private:
	unsigned int ID;
	EShaderType Type = EShaderType::None;
	unsigned int CreateShader(const std::string& Code, const EShaderType& Type);
	unsigned int CreateProgram(const unsigned int& VsId, const unsigned int& FsId);
public:
	inline unsigned int GetID()const { return ID; }
	inline EShaderType GetShaderType()const { return Type;}
	inline void Use()const {assert(ID && "Invalid Shader Id");glUseProgram(ID);}
	inline GLint GetUniformLocation(const std::string& name) { return glGetUniformLocation(ID, name.c_str());}
	inline void SetInt(const std::string& name, const GLint& value) { glUniform1i(GetUniformLocation(name), value); }
};

