#pragma once
#include<DMPCH.h>
#include<Core/Core.h>
#include<Tool/Util/Util.h>
#include<Core/Render/Shader.h>
#include<Core/Render/Texture/Texture.h>
#include<Core/Container/Array.h>
#include<Core/Container/UnOrderedMap.h>
namespace DM
{
	template<typename T>
	class AssetRegistry
	{
		UnOrderedMap<std::string, Ref<T>>Registry;
	public:
		inline bool HasAsset(const std::string& name)const;
		inline Ref<T>GetAsset(const std::string& name)const;
		Array<Ref<T>>GetAllAsset()const;
		Ref<T>Register(const std::string& assetPath);
		void Register(Ref<T> asset);
		void Register(Array<Ref<T>>assets);
		void UnRegisterAllAsset();
	};
	template<typename T>
	inline bool AssetRegistry<T>::HasAsset(const std::string& name)const
	{
		if (Registry.find(name) != Registry.end())return true;
		return false;
	}

	template<typename T>
	inline Ref<T> AssetRegistry<T>::GetAsset(const std::string& name) const
	{
		Ref<T> ret;
		if (HasAsset(name))
		{
			ret = Registry.at(name);
		}
		return ret;
	}

	template<typename T>
	Array<Ref<T>> AssetRegistry<T>::GetAllAsset() const
	{
		Array<Ref<T>> ret(Registry.size());
		for (const auto& In : Registry)
		{
			ret.push_back(In.second);
		}
		return ret;
	}

	template<typename T>
	Ref<T> AssetRegistry<T>::Register(const std::string& assetPath)
	{
		std::string name = Util::GetFileName(assetPath,false);
		if (HasAsset(name))return GetAsset(name);
		else
		{
			Ref<T>Asset = T::Create(assetPath);
			Registry[name] = Asset;
			return Asset;
		}
		return Ref<T>();
	}
	template<typename T>
	inline void AssetRegistry<T>::Register(Ref<T>asset)
	{
		std::string name = asset->GetName();
		if (!HasAsset(name))
		{
			Registry[name] = asset;
		}
		return;
	}
	template<typename T>
	inline void AssetRegistry<T>::Register(Array<Ref<T>>assets)
	{
		for (const auto& asset : assets)
		{
			Register(asset);
		}
	}
	template<typename T>
	inline void AssetRegistry<T>::UnRegisterAllAsset()
	{
		Registry.clear();
	}
}


