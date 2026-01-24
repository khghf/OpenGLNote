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
		static Ref<Shader>			GetShader(const std::string& name);
		static Ref<Texture2D>		GetTexture2D(const std::string& name);
	};
}
