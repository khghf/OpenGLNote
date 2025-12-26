#include<DMPCH.h>
#include "OpenGLShader.h"
#include<glad/glad.h>
#include<Tool/Util/GameStatic.h>
#include<Core/Core.h>
#include<regex>
namespace DM
{
	static EShaderType StringToOpenGlShaderType(const std::string str)
	{
		if (str == "vertex")
		{
			return EShaderType::VS;
		}
		else if (str == "fragment")
		{
			return EShaderType::FS;
		}
		DM_CORE_ASSERT(false,"{}","Unknown shader type!");
		return EShaderType::None;
	}
	OpenGlShader::OpenGlShader(const std::string_view& glslCodePath)
	{
		const std::string glslCode = GameStatic::LoadText(glslCodePath.data());
		std::unordered_map<std::string, std::string>type_Code = ProcessGLSLCode(glslCode);
		GLuint ID = glCreateProgram();
		std::vector<GLuint>shaderIDs;
		for (const auto& it : type_Code)
		{
			shaderIDs.push_back(CreateShader(it.second, StringToOpenGlShaderType(it.first)));
			glAttachShader(ID, *(shaderIDs.end()-1));
		}
		glLinkProgram(ID);
		this->m_Id = ID;
		CheckProgramLinkStatus(*this);
		for (const auto id : shaderIDs)
		{
			glDeleteShader(id);
		}
	}

	OpenGlShader::OpenGlShader(std::string_view VsCode, std::string_view FsCode)
	{
		CreateShader(VsCode, EShaderType::VS);
		uint32_t VsID = this->m_Id;
		CreateShader(FsCode, EShaderType::FS);
		uint32_t FsID = this->m_Id;
		CreateProgram(VsID, FsID);
		this->Type = EShaderType::PS;
	}

	OpenGlShader::OpenGlShader(const unsigned int& VSID, const unsigned int& FSID, const std::string& Name)
	{
		this->Type = EShaderType::PS;
		CreateProgram(VSID, FSID);
	}

	OpenGlShader::~OpenGlShader()
	{
		if (Type == EShaderType::PS)
		{
			glDeleteProgram(this->m_Id);
		}
	}

	unsigned int OpenGlShader::CreateShader(std::string_view Code, const EShaderType& Type)
	{
		unsigned int ID = 0;
		GLenum type = GL_VERTEX_SHADER;
		if (Type == EShaderType::VS)type = GL_VERTEX_SHADER;
		else if (Type == EShaderType::FS)type = GL_FRAGMENT_SHADER;
		ID = glCreateShader(type);
		const char* Code_cstr = Code.data();
		glShaderSource(ID, 1, &Code_cstr, NULL);
		glCompileShader(ID);
		this->m_Id = ID;
		const bool& Success = OpenGlShader::CheckShaderCompStatus(*this);
		DM_CORE_ASSERT(Success, "{},{}","Compile failed.Source Code",Code.data());
		return ID;
	}

	unsigned int OpenGlShader::CreateProgram(const unsigned int& VsId, const unsigned int& FsId)
	{
		const unsigned int PID = glCreateProgram();
		glAttachShader(PID, VsId);
		glAttachShader(PID, FsId);
		glLinkProgram(PID);
		this->m_Id = PID;
		glDeleteShader(VsId);
		glDeleteShader(FsId);
		OpenGlShader::CheckProgramLinkStatus(*this);
		return PID;
	}

	bool OpenGlShader::CheckShaderCompStatus(const OpenGlShader& shader)
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
			DM_CORE_ASSERT(false, "{},{}", "ERROR:program link failed\nInfoLog: ", InfoLog);
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


	bool OpenGlShader::CheckProgramLinkStatus(const OpenGlShader& shader)
	{
		const unsigned int& Id = shader.GetID();
		GLint Success = GL_FALSE;
		glGetProgramiv(Id, GL_LINK_STATUS, &Success);
		if (Success == GL_FALSE)
		{
			GLint LogLength = 0;
			glGetProgramiv(Id, GL_INFO_LOG_LENGTH, &LogLength);
			char* InfoLog = new char[LogLength + 1];
			glGetProgramInfoLog(Id, LogLength, NULL, InfoLog);
			InfoLog[LogLength] = '\0';
			DM_CORE_ASSERT(false, "{},{}", "ERROR:program link failed\nInfoLog: ", InfoLog);
			delete[] InfoLog;
			GLint attached;
			glGetProgramiv(Id, GL_ATTACHED_SHADERS, &attached);
			std::cout << "附加后着色器数量：" << attached << std::endl;
			return false;
		}
		return true;
	}
	std::unordered_map<std::string, std::string> OpenGlShader::ProcessGLSLCode(const std::string& glslCode)
	{
		std::string content = glslCode;
		content = std::regex_replace(content, std::regex(R"(/\*[\s\S]*(\*/))",std::regex::nosubs), "");	//删除多行注释  /**/
		content = std::regex_replace(content, std::regex(R"(//.*)", std::regex::nosubs), "");					//删除单行注释  //
		
		std::unordered_map<std::string, std::string>res;
		/*std::regex re(R"(#type\s+(vertex|fragment)([\s\S]*)(?!=#type|$))");
		std::sregex_iterator it(content.begin(), content.end(), re);
		std::sregex_iterator end;
		while (it != end)
		{
			std::smatch match = *it;
			res[match[1].str()] = match[2].str();
			++it;
		}*/
		std::regex re(R"(#type\s+(vertex|fragment))");
		std::sregex_token_iterator it_code(content.begin(), content.end(), re, -1);
		std::sregex_token_iterator end_code;
		std::sregex_token_iterator it_name(content.begin(), content.end(), re,1);
		while (it_code != end_code)
		{
			if (it_code->str().empty()) 
			{
				++it_code; 
				continue;
			}
			res[it_name->str()] = it_code->str();
			//LOG_Core_INFO("{}", it_code->str());
			++it_code;
			++it_name;
		}
		return res;
	}
}

