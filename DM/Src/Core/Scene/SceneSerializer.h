#pragma once
#include<Core/MMM/Reference.h>
namespace DM
{
	class Scene;
	class SceneSerializer
	{
	public:
		SceneSerializer() = default;
		SceneSerializer(Ref<Scene>scene);
		void Serialize(const std::string& filepath);
		void DeSerialize(const std::string& filepath);
		void SetContext(Ref<Scene>context) { m_Context = context; }
	private:
		Ref<Scene>m_Context;
	};
}


