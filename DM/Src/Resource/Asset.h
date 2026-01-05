#pragma once
#include<string>
namespace DM
{
	enum class EAssetsCategory :uint8_t//资源类型
	{
		Asset,
		Texture, Texture2D,
		Shader,
	};
	class Asset
	{
	public:
		Asset() = default;
		virtual ~Asset() = default;
		std::string GetName()const { return m_Name; };
		std::string GetPath()const { return m_Path; };
	public:
		constexpr static EAssetsCategory s_AssetsCategory = EAssetsCategory::Asset;
	protected:
		std::string m_Name;
		std::string m_Path;
	};
}
