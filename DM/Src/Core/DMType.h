#pragma once
#include<memory>
//#include<glad/glad.h>
//#include<json.hpp>
namespace DM
{
	template<typename T>
	using SPtr = std::shared_ptr<T>;
	template<typename T>
	using UPtr = std::unique_ptr<T>;
	template<typename T>
	using WPtr = std::weak_ptr<T>;
	//using Json = nlohmann::json;
	enum class EShaderType :uint8_t//着色器类型
	{
		None,
		VS,//顶点着色器
		FS,//片段着色器
		PS,//着色程序
	};
	enum class EAssetsType :uint8_t//资源类型
	{
		None,
		Texture2D,
		Shader,
	};

}
