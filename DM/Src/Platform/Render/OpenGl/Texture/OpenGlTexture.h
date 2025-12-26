#pragma once
#include<Core/Render/Texture/Texture.h>
namespace DM
{
	class OpenGlTexture2D:public Texture2D
	{
	public:
		OpenGlTexture2D( const std::string_view& path);
		~OpenGlTexture2D();
		virtual void Bind(uint32_t unit=0) override;
		virtual uint32_t GetWidth() const override { return m_Width; };
		virtual uint32_t GetHeight() const override { return m_Height; };
	private:
		uint32_t m_Width=-1, m_Height=-1;
		uint32_t m_Id=-1;
		std::string m_Path;

	};
}