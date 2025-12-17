#pragma once
#include"Shader.h"
#include"Texture2D.h"
#include"AssetRegistry.h"
#include"DataType.h"
#include<string>
#include"IManager.h"
#include<vector>
//资源加载在Window的构造函数中
class Asset;
class AssetManager:public ISingletion<AssetManager>
{
	friend class ISingletion<AssetManager>;
	using UTextureRegistry = AssetRegistry<Texture2D>;	UTextureRegistry Texture2DRegistry;
	using UShaderRegistry = AssetRegistry<Shader>;		UShaderRegistry ShaderRegistry;
public:
	~AssetManager();
private:
	AssetManager();
	AssetManager(const AssetManager&) = delete;
	AssetManager(AssetManager&) = delete;
	AssetManager(AssetManager&&) = delete;
	AssetManager& operator=(const AssetManager&) = delete;
	AssetManager& operator=(AssetManager&&) = delete;
	void LoadGameAsset();
	void PostLoadGameAsset();
	template<typename T>
	void RegisterAsset(const std::vector<std::string>& Paths, AssetRegistry<T>&Registry);
public:
	template<typename T>
	SPtr<T>GetAsset(const std::string& Name)const;
	template<typename T>
	SPtr<T>GetAsset(const char str [])const;
	template<typename T>
	std::vector<SPtr<T>>GetAllAsset()const;
};
template<typename T>
inline void AssetManager::RegisterAsset(const std::vector<std::string>& Paths, AssetRegistry<T>& Registry)
{
    if (Paths.size() == 0)return;
    for (const auto& path : Paths)
    {
        Registry.Register(path);
    }
}

template<typename T>
SPtr<T> AssetManager::GetAsset(const std::string& Name)const
{
    SPtr<T>ret;
    if constexpr (std::is_same<T, Texture2D>::value)
    {
        ret = Texture2DRegistry.GetAsset(Name);
    }
    else if constexpr (std::is_same<T, Shader>::value)
    {
        ret = ShaderRegistry.GetAsset(Name);
    }
    return ret;
}

template<typename T>
SPtr<T> AssetManager::GetAsset(const char str[]) const
{
    std::string Str(str);
    return GetAsset<T>(Str);
}

template<typename T>
std::vector<SPtr<T>> AssetManager::GetAllAsset() const
{
    std::vector<SPtr<T>>ret;
    if(std::is_same<T, Texture>::value)
    {
        ret = Texture2DRegistry.GetAllAsset();
    }
    else if(std::is_same<T, Shader>::value)
    {
        ret = ShaderRegistry.GetAllAsset();
    }
    return ret;
}

