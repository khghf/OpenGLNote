#pragma once
#include"Texture.h"
#include<Core/Math/Vector.h>
namespace DM
{
	class TextureAtlas 
	{
	public:
		TextureAtlas(Ref<Texture2D>atlas, Vector2 cellsize);
	private:
		Ref<Texture2D>m_Atlas;
	};
}
