#include "Texture2D.h"
#include"stb-master/stb_image.h"
#include<GameStatic.h>
#include<Util.h>
Texture2D::Texture2D()
{
    AssetsType = EAssetsType::Texture2D;
    glGenTextures(1, &Id);
	Type = GL_TEXTURE_2D;
	Bind(0);
	//设置环绕方式l
	glTexParameteri(Type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(Type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//设置过滤方式
	if (!bUseMipmap)
	{
		glTexParameteri(Type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//线性
		glTexParameteri(Type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//邻近
	}
	else
	{
		glTexParameteri(Type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);//层级内外线性
		glTexParameteri(Type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	UnBind();
}
Texture2D::Texture2D(const std::string& Path, int DesiredChannel):Texture2D()
{
    this->Name = GameStatic::ConvertPathToName(Path);
    this->Path = Path;
    stbi_set_flip_vertically_on_load(true);
    int Channel = 0;
    unsigned char* Data = stbi_load(Path.c_str(), &this->Width, &this->Height, &Channel, DesiredChannel);
    if (Data)
    {
       /* for (int i = 0; i < Width * Height * 4;)
        {
            Util::Print((int)Data[i], (int)Data[++i], (int)Data[++i], (int)Data[++i]);
        }*/
        this->LoadedImgFormat = 0;// 读取的图片的数据格式
        this->InternalFormat = 0;//纹理内部存储格式
        DesiredChannel = DesiredChannel == 0 ? Channel : DesiredChannel;//Data的通道数
        // 根据实际返回的通道数（desiredChannels 可能强制转换了通道）判断
        if (DesiredChannel == 1)
        {
            this->LoadedImgFormat = GL_RED;
            this->InternalFormat = GL_R8;  // 内部存储格式：单通道8位
        }
        else if (DesiredChannel == 3)
        {
            this->LoadedImgFormat = GL_RGB;
            this->InternalFormat = GL_RGB8; // 三通道8位
        }
        else if (DesiredChannel == 4)
        {
            //Util::Print("GL_RGBA8");
            this->LoadedImgFormat = GL_RGBA;
            this->InternalFormat = GL_RGBA8; // 四通道8位
        }
        else
        {
            assert(false && "Unsupported desired channels");
        }
        Bind(0);
        glTexImage2D(
            GL_TEXTURE_2D,              // 纹理目标（如 GL_TEXTURE_2D）
            0,                      // 基础层级
            this->InternalFormat,    // 纹理的内部存储格式
            this->Width,             // 宽度
            this->Height,            // 高度
            0,                      // 边界（必须为0）
            this->LoadedImgFormat,   // 读取的图片的数据格式
            GL_UNSIGNED_BYTE,       // 输入数据类型（stbi_load 返回 unsigned char）
            Data                    // 像素数据
        );
        if (this->bUseMipmap)glGenerateMipmap(this->Type);
        UnBind();
    }
    else
    {
        assert(false && "stbi_load load data failed");
    }
    stbi_image_free(Data);
}
SPtr<Texture2D> Texture2D::LoadTexture2D(const std::string& Path,int DesiredChannel)
{
    SPtr<Texture2D> Tex(new Texture2D());
    Tex->Name = GameStatic::ConvertPathToName(Path);
    Tex->Path = Path;
    stbi_set_flip_vertically_on_load(true);
    int Channel = 0;
    unsigned char* Data = stbi_load(Path.c_str(), &Tex->Width, &Tex->Height, &Channel, DesiredChannel);
    if (Data)
    {
        Tex->LoadedImgFormat = 0;// 读取的图片的数据格式
        Tex->InternalFormat = 0;//纹理内部存储格式
        DesiredChannel = DesiredChannel == 0 ? Channel : DesiredChannel;//Data的通道数
        // 根据实际返回的通道数（desiredChannels 可能强制转换了通道）判断
        if (DesiredChannel == 1)
        {
            Tex->LoadedImgFormat = GL_RED;
            Tex->InternalFormat = GL_R8;  // 内部存储格式：单通道8位
        }
        else if (DesiredChannel == 3)
        {
            Tex->LoadedImgFormat = GL_RGB;
            Tex->InternalFormat = GL_RGB8; // 三通道8位
        }
        else if (DesiredChannel == 4)
        {
            Tex->LoadedImgFormat = GL_RGBA;
            Tex->InternalFormat = GL_RGBA8; // 四通道8位
        }
        else
        {
            assert(false && "Unsupported desired channels");
        }
        Tex->Bind(0);
        glTexImage2D(
            Tex->Type,              // 纹理目标（如 GL_TEXTURE_2D）
            0,                      // 基础层级
            Tex->InternalFormat,    // 纹理的内部存储格式
            Tex->Width,             // 宽度
            Tex->Height,            // 高度
            0,                      // 边界（必须为0）
            Tex->LoadedImgFormat,   // 读取的图片的数据格式
            GL_UNSIGNED_BYTE,       // 输入数据类型（stbi_load 返回 unsigned char）
            Data                    // 像素数据
        );
        if (Tex->bUseMipmap)glGenerateMipmap(Tex->Type);
    }
    stbi_image_free(Data);
	return Tex;
}

