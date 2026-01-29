#pragma once
#include<Reflect/reflection.h>
#include<Reflect/ReflectMarco.h>
#include<json/json.hpp>
#include<entt/entt.hpp>
#include"Tool/Util/GameStatic.h"
#include<GObject.gen.h>
namespace DM
{
	class CLASS() GObject
	{
		REFLECT_BODY()
	public:
		GObject();
		virtual~GObject()=default;
	public:
		virtual void Start() ;
		virtual void Update(float DeltaTime);
		virtual void OnDestroy();
		inline void EnableUpdate(const bool& bEnable) { bEnableUpdate = bEnable; }
		inline bool IsEnableUpdate()const { return bEnableUpdate; }
	private:
		PROPERTY()
			bool bEnableUpdate;
		PROPERTY()
			int test1=100;
		PROPERTY()
			int test2=200;
		PROPERTY()
			std::string name;
		PROPERTY()
			std::vector<int> vec;
		PROPERTY()
			std::vector<float> vec2;
		PROPERTY()
			std::map<float,int> map;
		PROPERTY()
			bool bEnableUpdate2;
	};
}
