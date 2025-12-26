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
	


}
