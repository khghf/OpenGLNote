#pragma once
#include<unordered_map>
#include<string>
#include"DataType.h"
#include"GameStatic.h"
#include"Util.h"
#include<vector>
#include"Shader.h"
template<typename T>
class AssetRegistry
{
	std::unordered_map<std::string, SPtr<T>>Registry;
public:
	inline bool HasAsset(const std::string& Name)const;
	inline SPtr<T>GetAsset(const std::string& Name)const;
	std::vector<SPtr<T>>GetAllAsset()const;
	SPtr<T>Register(const std::string& AssetPath);
	void Register(SPtr<T> Asset);
	void Register(std::vector<SPtr<T>>Assets);
	void UnRegisterAllAsset();
};
template<typename T>
inline bool AssetRegistry<T>::HasAsset(const std::string& Name)const
{
	if (Registry.find(Name) != Registry.end())return true;
	return false;
}

template<typename T>
inline SPtr<T> AssetRegistry<T>::GetAsset(const std::string& Name) const
{
	SPtr<T> ret;
	if (HasAsset(Name))
	{
		ret = Registry.at(Name);
	}
	return ret;
}

template<typename T>
std::vector<SPtr<T>> AssetRegistry<T>::GetAllAsset() const
{
	std::vector<SPtr<T>> ret(Registry.size());
	for (const auto& In : Registry)
	{
		ret.push_back(In.second);
	}
	return ret;
}

template<typename T>
SPtr<T> AssetRegistry<T>::Register(const std::string& AssetPath)
{
	std::string name = GameStatic::ConvertPathToName(AssetPath);
	//Util::Print(name);
	if (HasAsset(name))return GetAsset(name);
	else
	{
		SPtr<T>Asset = std::make_shared<T>(AssetPath);
		Registry[name]=Asset;
		return Asset;
	}
	return SPtr<T>();
}

template<typename T>
inline void AssetRegistry<T>::Register(SPtr<T>Asset)
{
	std::string name = Asset.get()->GetName();
	if (!HasAsset(name))
	{
		Registry[name] = Asset;
	}
	return;
}

template<typename T>
inline void AssetRegistry<T>::Register(std::vector<SPtr<T>>Assets)
{
	for (const auto& Asset : Assets)
	{
		Register(Asset);
	}
}

template<typename T>
inline void AssetRegistry<T>::UnRegisterAllAsset()
{
	Registry.clear();
}

