#pragma once
#include<DMPCH.h>
#include<Resource/Asset.h>
namespace DM
{
	class Shader:public Asset
	{
	public:
		Shader();
		virtual ~Shader();
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		static Shader* Create(std::string_view vsCodePath, std::string_view fsCodePath);
		static Shader* Create(std::string_view glslCodePath);
	private:
	};
}