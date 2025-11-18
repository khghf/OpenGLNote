#pragma once
#include"Texture.h"

#include<vector>
#include"DataType.h"
class Texture2D :public Texture
{
public:
	Texture2D();
	~Texture2D()=default;
	Texture2D(const std::string&Path, int DesiredChannel=0);
	static SPtr<Texture2D>LoadTexture2D(const std::string& Path,int DesiredChannel=0);
	inline void SetWarp(GLint WarpSModel = GL_REPEAT, GLint WarpTModel = GL_REPEAT)
	{
		Bind(0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WarpSModel);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WarpTModel);
		UnBind();
	}
	inline void SetFilter(GLint MINFilterModel, GLint MAGFilterModel)
	{
		Bind(0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MINFilterModel);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MAGFilterModel);
		UnBind();
	}
private:
	int Width = 0;
	int Height = 0;
	bool bUseMipmap=true;
	GLint InternalFormat = 0;//纹理的颜色通道
	GLenum LoadedImgFormat = 0;//读取图片的颜色通道(RGB、RGBA、R..........)
};