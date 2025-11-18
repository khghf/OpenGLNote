#include "AssetManager.h"
#include<fstream>
#include<iostream>
#include<GameStatic.h>
#include<Util.h>
#include<type_traits>
AssetManager::~AssetManager()
{
    Util::Print("~AssetManager");
}
AssetManager::AssetManager()
{
    LoadGameAsset();
}

void AssetManager::LoadGameAsset()
{
    Json Config;
    std::ifstream ConFile;
    try
    {
        ConFile.open("../Config/Config.json");
        ConFile >> Config;
        ConFile.close();
        const std::string ShaderFloderPath = Config["Asset"]["ShaderFolder"];
        const std::string TextureFloderPath = Config["Asset"]["TextureFolder"];
        const std::vector<std::string>&ShaderPaths = GameStatic::GetAllFilePath(ShaderFloderPath, true);
        const std::vector<std::string>&TexturePaths = GameStatic::GetAllFilePath(TextureFloderPath,true);
        RegisterAsset(ShaderPaths, ShaderRegistry);
        RegisterAsset(TexturePaths, Texture2DRegistry);
    }
    catch (const std::exception&e)
    {
        std::cerr << "AssetManager:load config file failed" <<e.what()<< std::endl;
    }
    PostLoadGameAsset();
}

void AssetManager::PostLoadGameAsset()
{
    //将加载好了的着色器链接成着色程序
    std::vector<SPtr<Shader>>Shaders = ShaderRegistry.GetAllAsset();
    std::unordered_map<std::string, std::vector<SPtr<Shader>>>LinkShader;
    auto GetNameWithOutSuffix = [](const std::string&str)->std::string {
        std::string ret;
        const auto& Index = str.find_last_of('.');
        ret = str.substr(0, Index);
        return ret;
        };
    for (const auto& shader : Shaders)
    {
        if (!shader)continue;
        std::string name = GetNameWithOutSuffix(shader.get()->GetName());
        //Util::Print("0000*********" ,name);
        LinkShader[name].push_back(shader);
    }
    std::vector<SPtr<Shader>>Programs;
    for (const auto& In : LinkShader)
    {
        unsigned int  VsId;
        unsigned int  FsId;
        Shader* s1 = In.second[0].get();
        Shader* s2 = In.second[1].get();
        if (s1->GetShaderType() == EShaderType::VS)
        {
            VsId = s1->GetID();
            FsId = s2->GetID();
        }
        else
        {
            VsId = s2->GetID();
            FsId = s1->GetID();
        }
        Programs.push_back(std::shared_ptr<Shader>(new Shader(VsId,FsId,GetNameWithOutSuffix(s1->GetName()))));
    }
    ShaderRegistry.UnRegisterAllAsset();
    ShaderRegistry.Register(Programs);
}


