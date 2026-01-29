#pragma once
#include"reflection.h"
#include<typeindex>
#define ARRAY_COUNT(x)sizeof(x)/sizeof(x[0])
#define TOSTR(x)#x
#define ConstructRClass(ClassName,nameSpace)\
		static  reflect::RClass* ConstructRClass_##ClassName()\
		{\
			static  reflect::RClass class_##ClassName;\
			if(reflect::RObjectSetter::IsAlreadyConstruct(&class_##ClassName))return &class_##ClassName;\
			reflect::RObjectSetter::SetName(&class_##ClassName, #ClassName);\
			reflect::RObjectSetter::SetHashCode(&class_##ClassName,typeid(nameSpace::ClassName).hash_code());\
			return &class_##ClassName;\
		};

#define ConstructRFunction(FunctionName,SuperClassName,nameSpace)\
		static reflect::RFunction* ConstructRFunction_##FunctionName()\
		{\
			static reflect::RFunction function_##FunctionName(&nameSpace::SuperClassName::FunctionName);\
			if(reflect::RObjectSetter::IsAlreadyConstruct(&function_##FunctionName))return &function_##FunctionName;\
			reflect::RObjectSetter::SetName(&function_##FunctionName, #FunctionName);\
			reflect::RObjectSetter::SetSuperClass(&function_##FunctionName, ConstructRClass_##SuperClassName());\
			return &function_##FunctionName;\
		};

#define ConstructRProperty(PropertyName,SuperClassName,nameSpace)\
		static  reflect::RProperty* ConstructRProperty_##PropertyName()\
		{\
			static  reflect::RProperty property_##PropertyName(&nameSpace::SuperClassName::PropertyName);\
			if(reflect::RObjectSetter::IsAlreadyConstruct(&property_##PropertyName))return &property_##PropertyName;\
			reflect::RObjectSetter::SetName(&property_##PropertyName, #PropertyName);\
			reflect::RObjectSetter::SetSuperClass(&property_##PropertyName, ConstructRClass_##SuperClassName());\
			return &property_##PropertyName;\
		};
namespace reflect
{
	struct Is_Pointer
	{
		template<typename Ty>
		constexpr static bool Val(Ty&& obj)
		{
			return std::is_pointer_v<std::remove_reference_t<Ty>>;
		}
	};
	template<typename tTy, typename sTy>
	static bool	IsChildOf(sTy&& source)
	{
		using s1 = std::remove_reference_t<sTy>;
		using s2 = std::remove_pointer_t<s1>;
		using s3 = std::remove_cv_t<s2>;
		reflect::RClass* rclass = GetRClass(typeid(s3).hash_code());
		if (rclass == nullptr)return false;
		return rclass->_IsChildOf<tTy>();
		std::is_pointer_v
	}
	template<typename>
	constexpr bool Is_Smart_Ptr= false;
	template<typename Ty>
	constexpr bool Is_Smart_Ptr<std::shared_ptr<Ty>> = true;
	template<typename Ty>
	constexpr bool Is_Smart_Ptr<const std::shared_ptr<Ty>> = true;
	template<typename Ty>
	constexpr bool Is_Smart_Ptr<std::shared_ptr<Ty>&> = true;
	template<typename Ty>
	constexpr bool Is_Smart_Ptr<const std::shared_ptr<Ty>&> = true;


	template<typename Ty>
	constexpr bool Is_Smart_Ptr<std::weak_ptr<Ty>> = true;
	template<typename Ty>
	constexpr bool Is_Smart_Ptr<const std::weak_ptr<Ty>> = true;
	template<typename Ty>
	constexpr bool Is_Smart_Ptr<std::weak_ptr<Ty>&> = true;
	template<typename Ty>
	constexpr bool Is_Smart_Ptr<const std::weak_ptr<Ty>&> = true;

	template<typename Ty>
	constexpr bool Is_Smart_Ptr<std::unique_ptr<Ty>> = true;
	template<typename Ty>
	constexpr bool Is_Smart_Ptr<const std::unique_ptr<Ty>> = true;
	template<typename Ty>
	constexpr bool Is_Smart_Ptr<std::unique_ptr<Ty>&> = true;
	template<typename Ty>
	constexpr bool Is_Smart_Ptr<const std::unique_ptr<Ty>&> = true;
}
#define TO_JSON_VAL(className)\
void to_json(::nlohmann::json&j,const className&obj)\
{\
	j["Type"]=TOSTR(className);\
	j["ActualType"]=obj.GetTypeName();\
	to_json_internal(j,&obj);\
}
#define TO_JSON_PTR(className)\
void to_json(::nlohmann::json&j,const className*obj)\
{\
	if(obj==nullptr)return;\
	j["Type"]=TOSTR(className##*);\
	j["ActualType"]=obj->GetTypeName();\
	to_json_internal(j,obj);\
}
#define TO_JSON_SPTR(className)\
void to_json(::nlohmann::json&j,const std::shared_ptr<className>&obj)\
{\
	className*ptr=obj.get();\
	if(ptr==nullptr)return;\
	j["Type"]=TOSTR(std::shared_ptr<className>);\
	j["ActualType"]=obj->GetTypeName();\
	to_json_internal(j,ptr);\
}
#define TO_JSON_WPTR(className)\
void to_json(::nlohmann::json&j,const std::weak_ptr<className>&obj)\
{\
	className*ptr=obj.lock().get();\
	if(ptr==nullptr)return;\
	j["Type"]=TOSTR(std::weak_ptr<className>);\
	j["ActualType"]=ptr->GetTypeName();\
	to_json_internal(j,ptr);\
}
#define TO_JSON_UPTR(className)\
void to_json(::nlohmann::json&j,const std::unique_ptr<className>&obj)\
{\
	className*ptr=obj.get();\
	if(ptr==nullptr)return;\
	j["Type"]=TOSTR(std::unique_ptr<className>);\
	j["ActualType"]=obj->GetTypeName();\
	to_json_internal(j,ptr);\
}
#define DEF_TO_JSON(className)\
void to_json_internal(::nlohmann::json&j,const className *obj)\
{\
	reflect::RClass*rclass=reflection::GetRClass(obj->GetTypeName());\
	if(rclass!=nullptr)rclass->ToJson(j,obj);\
}\
TO_JSON_VAL(className)\
TO_JSON_PTR(className)\
TO_JSON_SPTR(className)\
TO_JSON_WPTR(className)\
TO_JSON_UPTR(className)

#define FROM_JSON_VAL(className)\
void from_json(const::nlohmann::json&j, className&obj)\
{\
	from_json_internal(j,&obj);\
}
#define FROM_JSON_PTR(className)\
void from_json(const::nlohmann::json&j, className*obj)\
{\
	if(obj==nullptr)return;\
	from_json_internal(j,obj);\
}
#define FROM_JSON_SPTR(className)\
void from_json(const::nlohmann::json&j, std::shared_ptr<className>&obj)\
{\
	className*ptr=obj.get();\
	if(ptr==nullptr)return;\
	from_json_internal(j,ptr);\
}
#define FROM_JSON_WPTR(className)\
void from_json(const::nlohmann::json&j, std::weak_ptr<className>&obj)\
{\
	className*ptr=obj.lock().get();\
	if(ptr==nullptr)return;\
	from_json_internal(j,ptr);\
}
#define FROM_JSON_UPTR(className)\
void from_json(const::nlohmann::json&j, std::unique_ptr<className>&obj)\
{\
	className*ptr=obj.get();\
	if(ptr==nullptr)return;\
	from_json_internal(j,ptr);\
}

#define DEF_FROM_JSON(className)\
void from_json_internal(const ::nlohmann::json&j,className *obj)\
{\
	if(!j.contains("ActualType")){std::cerr<<"Deserialize failed:"<<#className<<std::endl;return;}\
	reflect::RClass*rclass=reflection::GetRClass(j["ActualType"].get<std::string>());\
	if(rclass!=nullptr)rclass->FromJson(j,obj);\
}\
FROM_JSON_VAL(className)\
FROM_JSON_PTR(className)\
FROM_JSON_SPTR(className)\
FROM_JSON_WPTR(className)\
FROM_JSON_UPTR(className)