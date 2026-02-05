#pragma once
#include<Core/Reflection/Mirror/ReflectMarco.h>
#include<Core/Reflection/Mirror/mirror.h>
#include<Tool/Util/GameStatic.h>
#include<entt/entt.hpp>
#include<Core/MMM/Reference.h>
#include<unordered_set>
#include<Core/Log.h>
#include"GObject.gen.h"
namespace DM
{
	class GComponent;
	class CLASS() GObject
	{
		REFLECT_BODY()
	public:
		GObject();
		virtual~GObject()=default;
	public:
		virtual void Update(float DeltaTime);
		virtual void Destroy();
		virtual void OnDestroy();

		inline void EnableUpdate(const bool& bEnable) { bEnableUpdate = bEnable; }
		inline bool IsEnableUpdate()const { return bEnableUpdate; }
	private:
		PROPERTY()
			Ref<int>test;
		/*PROPERTY()
			std::unordered_set<std::pair<std::string, GComponent*>>_Components2;*/
		PROPERTY()
			bool bEnableUpdate;
	};
}
//REGISTER_TYPE(DM::GObject)
//REGISTER_PRIVATE_MEMBER(DM::GObject, test)
//REGISTER_PRIVATE_MEMBER(DM::GObject, bEnableUpdate)
