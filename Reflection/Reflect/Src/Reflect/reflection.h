#pragma once
#include "ReflectMarco.h"
#include"RClass.h"
#include"RFunction.h"
#include"RProperty.h"
#include<json/json.hpp>
#include<iostream>
using RClassConstructor = reflect::RClass * (*)();
using RFunctionConstructor = reflect::RFunction * (*)();
using RPropertyConstructor = reflect::RProperty * (*)();
using _TO_JSON_ = void(*)(::nlohmann::json& j,const void* obj);
using _FROM_JSON_ = void(*)(const ::nlohmann::json& j,void*obj);
struct RegistrationInfo
{
	RClassConstructor*SuperClasses;
	RClassConstructor Class;
	RFunctionConstructor*Functions;
	RPropertyConstructor*Properties;
	const  uint32_t SuperClassNum;
	const  uint32_t FunctionNum;
	const  uint32_t PropertyNum;
	_TO_JSON_ ToJson;
	_FROM_JSON_ FromJson;
};
//配合RegisterRegistrationInfo在dll导入初始化静态变量时注册
struct  CollectRegistrationInfo
{
	template<typename...Args>
	CollectRegistrationInfo(Args&&...arg)
	{
		RegisterRegistrationInfo(std::forward<Args>(arg)...);
	}
};
//注册收集到的信息，生成RClass,RFunction.....
void RegisterRegistrationInfo(const RegistrationInfo& Info);

namespace reflect
{
	//反射信息都是在运行前确定的不可在运行期修改所以没有提供修改接口但生成的Operator需要对其进行修改,所以提供RObjectSetter对其内部成员进行修改
	class RObjectSetter
	{
	public:
		static void SetName(reflect::RObject* obj, const std::string& val) { obj->_Name = val; }
		static void SetHashCode(reflect::RObject* obj, const size_t& val) { obj->_HashCode = val; }
		static void SetSuperClass(reflect::RObject* obj, reflect::RClass* val) { obj->_SuperClass = val; }
		static void AddRFunToRClass(reflect::RClass* obj, reflect::RFunction* val) { obj->_Functions[val->_Name] = val; }
		static void AddRProToRClass(reflect::RClass* obj, reflect::RProperty* val) { obj->_Properties[val->_Name] = val; }
		static bool IsAlreadyConstruct(reflect::RObject* obj) { return !obj->_Name.empty(); }
		static void AddSuperClass(reflect::RClass* obj, reflect::RClass* val) { obj->_SuperClasses.emplace_back(val); }
		static void SetToJson(reflect::RClass* obj, _TO_JSON_ to_json) { obj->_ToJson = to_json; }
		static void SetFromJson(reflect::RClass* obj, _FROM_JSON_ from_json) { obj->_FromJson= from_json; }
	};
}
Reflect_API reflect::RClass* GetRClass(const size_t& hashCode);
Reflect_API reflect::RFunction* GetRFunction(const size_t& hashCode, const std::string functionName);
Reflect_API reflect::RProperty* GetRProperty(const size_t& hashCode, const std::string propertyName);
class Reflect_API reflection
{
public:
	template<typename Class>
	static reflect::RClass* GetRClass() { return ::GetRClass(typeid(Class).hash_code()); }
	template<typename Class>
	static reflect::RFunction* GetRFunction(const std::string& functionName) { return GetRFunction(typeid(Class).hash_code(), functionName); }
	template<typename Class>
	static reflect::RProperty* GetRProperty(const std::string& propertyName) { return GetRProperty(typeid(Class).hash_code(), propertyName); }
	static reflect::RClass* GetRClass(const std::string& name);
};