#include<DMPCH.h>
#include "AssetManager.h"
#include<Tool/Util/GameStatic.h>
#include<type_traits>
#include<Core/Serialization.h>
#include<fstream>
namespace DM
{

    AssetManager::AssetManager()
    {
        LoadAsset();
    }
    AssetManager::~AssetManager()
    {

    }
    

    void AssetManager::LoadAsset()
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
            const Array<std::string>& ShaderPaths = GameStatic::GetAllFilePath(ShaderFloderPath, true);
            const Array<std::string>& TexturePaths = GameStatic::GetAllFilePath(TextureFloderPath, true);
            RegisterAsset(ShaderPaths, ShaderRegistry);
            RegisterAsset(TexturePaths, Texture2DRegistry);
        }
        catch (const std::exception& e)
        {
            std::cerr << "AssetManager:load config file failed" << e.what() << std::endl;
        }
        PostLoadAsset();
    }

    void AssetManager::PostLoadAsset()
    {
        //将加载好了的着色器链接成着色程序
        //Array<Ref<Shader>>Shaders = ShaderRegistry.GetAllAsset();
        //std::unordered_map<std::string, Array<Ref<Shader>>>LinkShader;
        //auto GetNameWithOutSuffix = [](const std::string& str)->std::string {
        //    std::string ret;
        //    const auto& Index = str.find_last_of('.');
        //    ret = str.substr(0, Index);
        //    return ret;
        //    };
        //for (const auto& shader : Shaders)
        //{
        //    if (!shader)continue;
        //    std::string name = GetNameWithOutSuffix(shader.get()->GetName());
        //    //Util::Print("0000*********" ,name);
        //    LinkShader[name].push_back(shader);
        //}
        //Array<Ref<Shader>>Programs;
        //for (const auto& In : LinkShader)
        //{
        //    unsigned int  VsId;
        //    unsigned int  FsId;
        //    Shader* s1 = In.second[0].get();
        //    Shader* s2 = In.second[1].get();
        //    if (s1->GetShaderType() == EShaderType::VS)
        //    {
        //        VsId = s1->GetID();
        //        FsId = s2->GetID();
        //    }
        //    else
        //    {
        //        VsId = s2->GetID();
        //        FsId = s1->GetID();
        //    }
        //    Programs.push_back(std::shared_ptr<Shader>(new Shader(VsId, FsId, GetNameWithOutSuffix(s1->GetName()))));
        //}
        //ShaderRegistry.UnRegisterAllAsset();
        //ShaderRegistry.Register(Programs);
    }
}



