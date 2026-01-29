#pragma once
#include<string>
#include<Core/Container/Array.h>
#include<Core/MMM/Reference.h>
#include<Reflect/ReflectMarco.h>
#include<FrameWork/GObject.h>
#include<GameStatic.gen.h>
namespace DM
{
	enum  class ENUM()  test
	{
		val = 1,
		val2 = 2
	};
	class Shader;
	class Texture2D;
	class GameStatic
	{
	public:
		static Ref<Shader>			GetShader(const std::string& name);
		static Ref<Texture2D>		GetTexture2D(const std::string& name);









		template<typename tTy,typename sTy>
		static bool	IsChildOf(sTy&&source)
		{
			using s1 = std::remove_reference_t<sTy>;
			using s2 = std::remove_pointer_t<s1>;
			using s3 = std::remove_cv_t<s2>;
			reflect::RClass* rclass = GetRClass(typeid(s3).hash_code());
			if (rclass == nullptr)return false;
			return rclass->_IsChildOf<tTy>();
		}
	};
}
