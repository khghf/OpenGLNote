#pragma once
#include<Asset.h>
class Texture :public Asset
{
public:
	Texture() = default;
	virtual ~Texture(){ glDeleteTextures(1, &this->Id); }
	inline void Bind(const GLenum& TexUnit) { TextureUnit = TexUnit; glActiveTexture(GL_TEXTURE0+TexUnit); glBindTexture(Type, Id); }
	inline void UnBind() { glActiveTexture(TextureUnit); glBindTexture(Type, 0); }
	inline GLenum GetTextureUnit()const { return TextureUnit;}
protected:
	GLuint Id=0;
	GLenum TextureUnit = 0;//绑定的纹理单元
	GLenum Type=0;//纹理类型
	Texture(Texture&) = delete;
	Texture(const Texture&) = delete;
	Texture(Texture&&) = delete;
	Texture& operator=(Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&&) = delete;
};