#pragma once
#include<memory>
#include<Reflect/ReflectMarco.h>
#define TOSTR(x)#x
#define DEC_TO_JSON(className)\
Reflect_API void to_json(::nlohmann::json&j,const className&obj);\
Reflect_API void to_json(::nlohmann::json&j,const className*obj);\
Reflect_API void to_json(::nlohmann::json&j,const std::shared_ptr<className>&obj);\
Reflect_API void to_json(::nlohmann::json&j,const std::weak_ptr<className>&obj);\
Reflect_API void to_json(::nlohmann::json&j,const std::unique_ptr<className>&obj);

#define DEC_FROM_JSON(className)\
Reflect_API void from_json(const ::nlohmann::json&j,className&obj);\
Reflect_API void from_json(const ::nlohmann::json&j,className*obj);\
Reflect_API void from_json(const ::nlohmann::json&j,std::shared_ptr<className>obj);\
Reflect_API void from_json(const ::nlohmann::json&j,std::weak_ptr<className>obj);\
Reflect_API void from_json(const ::nlohmann::json&j,std::unique_ptr<className>obj);