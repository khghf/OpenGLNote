#pragma once
#include<Resource/Asset.h>
#include<Core/Render/Shader.h>
#include<glad/glad.h>
#include<Core/Math/Matrix.h>
#include<glm/gtc/type_ptr.hpp>
namespace DM
{
	enum class EShaderType :uint8_t//着色器类型
	{
		None,
		VS,//顶点着色器
		FS,//片段着色器
		PS,//着色程序
	};
	class OpenGlShader :public Shader
	{
	public:
		OpenGlShader(const std::string_view& glslCodePath);
		//OpenGlShader(std::string_view Code, const EShaderType& Type);
		OpenGlShader(std::string_view VsCode, std::string_view FsCode);
		OpenGlShader(const unsigned int& VSID, const unsigned int& FSID, const std::string& Name);
		~OpenGlShader();
	private:
		unsigned int m_Id;
		EShaderType Type = EShaderType::None;
		unsigned int CreateShader(std::string_view Code, const EShaderType& Type);
		unsigned int CreateProgram(const unsigned int& VsId, const unsigned int& FsId);
		static bool CheckShaderCompStatus(const OpenGlShader& shader);
		static bool CheckProgramLinkStatus(const OpenGlShader& shader);
		std::unordered_map<std::string, std::string>ProcessGLSLCode(const std::string& glslCode);
	public:
		inline unsigned int GetID()const { return m_Id; }
		inline EShaderType GetShaderType()const { return Type; }
		virtual void Bind()override { assert(m_Id && "Bind Invalid Shader Id"); glUseProgram(m_Id); }
		virtual void UnBind()override { assert(m_Id && "UnBind Invalid Shader Id"); glUseProgram(0); }
		inline GLint GetUniformLocation(std::string_view name) { return glGetUniformLocation(m_Id, name.data()); }
		inline void UploadInt(std::string_view name, const GLint& value) { glUniform1i(GetUniformLocation(name), value); }
		inline void UploadMat4x4( std::string_view name, const Matrix4& matrix) { glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));}
	};
}


