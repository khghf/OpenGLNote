#include<DMPCH.h>
#include "GameStatic.h"

#include<Resource/AssetManager.h>
namespace DM
{
	Ref<Shader> GameStatic::GetShader(const std::string& name)
	{
		return AssetManager::GetInst()->GetAsset<Shader>(name);
	}
	Ref<Texture2D> GameStatic::GetTexture2D(const std::string& name)
	{
		return AssetManager::GetInst()->GetAsset<Texture2D>(name);
	}
}


