#pragma once
#include"RObject.h"
#include<unordered_map>
#include"RFunction.h"
#include"RProperty.h"
#include<iostream>
#include<queue>
namespace DM
{
	class GameStatic;
}
namespace reflect
{
	class RClass:public RObject
	{
		friend class RObjectSetter;
		friend class DM::GameStatic;
	public:
		RFunction* GetRFunction(const std::string& funName)const 
		{ 
			const auto& it = _Functions.find(funName);
			return it != _Functions.end() ? it->second : nullptr; 
		}
		RProperty* GetRProperty(const std::string& proName)const	
		{ 
			const auto& it = _Properties.find(proName);
			return it != _Properties.end() ? it->second : nullptr;
		}
		std::vector<RProperty*> GetRProperties()const
		{
			std::vector<RProperty*>pros;
			pros.reserve(_Properties.size());
			for (const auto&it:_Properties)
			{
				pros.push_back(it.second);
			}
			return pros;
		}
		template<typename VarType,typename Class>
		VarType GetVariable(const std::string& name,Class* obj)
		{
			RProperty* pro = GetRProperty(name);
			if (pro)return pro->GetValue<VarType>(obj);
			std::cerr << "no variable:" + name + "in class:" + _Name << std::endl;
			return VarType{};
		}
		template<typename VarType, typename Class>
		void SetVariable(const std::string& name, Class* obj, VarType&&var)
		{
			RProperty* pro = GetRProperty(name);
			if (pro) { pro->SetValue<VarType>(obj, std::forward<VarType>(var)); return; };
			std::cerr << "no variable:" + name + "in class:" + _Name << std::endl;
		}
		template<typename Class,typename...Args>
		inline std::any InvokeFun(const std::string& funName,Class&obj,Args...arg)
		{
			RFunction* fun = GetRFunction(funName);
			if(fun)return fun->Invoke(obj, std::forward<Args>(arg)...);
			std::cerr << "no function:" + funName + "in class:" + _Name << std::endl;
			return std::any{};
		}

		void  ToJson(::nlohmann::json&j,const void* obj) {_ToJson(j,obj); }
		void  FromJson(const ::nlohmann::json& j,void*obj) {_FromJson(j,obj); }
	private:
		template<typename tTy>
		bool _IsChildOf()
		{
			size_t tHash = typeid(tTy).hash_code();
			if (tHash == _HashCode)return true;
			std::queue<RClass*>q;
			auto push = [&q](std::vector<RClass*>&vec)
				{
					for (const auto& r : vec)
					{
						q.push(r);
					}
				};
			push(_SuperClasses);
			while (!q.empty())
			{
				RClass* r = q.front();
				if (tHash == r->_HashCode)return true;
				q.pop();
				push(r->_SuperClasses);
			}
			return false;
		}
	private:
		std::vector<RClass*>_SuperClasses;
		std::unordered_map<std::string_view, RFunction*>_Functions;
		std::unordered_map<std::string_view, RProperty*>_Properties;
		void(*_ToJson)(::nlohmann::json& j, const void* obj);
		void(*_FromJson)(const ::nlohmann::json& j,void*obj);
	};
}