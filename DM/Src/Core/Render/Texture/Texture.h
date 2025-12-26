#pragma once
#include<Resource/Asset.h>
#include<Core/Core.h>
#include<string_view>
namespace DM
{
	class Texture :public Asset
	{
	//public:
	//	Texture() = default;
	//	virtual ~Texture() { glDeleteTextures(1, &this->Id); }
	//	inline void Bind(const GLenum& TexUnit) { TextureUnit = TexUnit; glActiveTexture(GL_TEXTURE0 + TexUnit); glBindTexture(Type, Id); }
	//	inline void UnBind() { glActiveTexture(TextureUnit); glBindTexture(Type, 0); }
	//	inline GLenum GetTextureUnit()const { return TextureUnit; }
	//protected:
	//	GLuint Id = 0;
	//	GLenum TextureUnit = 0;//绑定的纹理单元
	//	GLenum Type = 0;//纹理类型
	//	Texture(Texture&) = delete;
	//	Texture(const Texture&) = delete;
	//	Texture(Texture&&) = delete;
	//	Texture& operator=(Texture&) = delete;
	//	Texture& operator=(const Texture&) = delete;
	//	Texture& operator=(Texture&&) = delete;
	public:
		virtual ~Texture() = default;
		virtual void Bind(uint32_t unit=0) = 0;
		virtual uint32_t GetWidth() const= 0;
		virtual uint32_t GetHeight() const= 0;
	public:
		constexpr static EAssetsCategory s_AssetsCategory = EAssetsCategory::Texture;
	};
	class Texture2D :public Texture
	{
	public:
		static Ref<Texture2D>Create( const std::string_view& path);
	};
}
