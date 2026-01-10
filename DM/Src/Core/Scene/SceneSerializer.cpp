#include "DMPCH.h"
#include "SceneSerializer.h"
#include"Scene.h"
#include<yaml-cpp/yaml.h>
#include<filesystem>
#include<Core/Core.h>
#include<Core/Scene/Entity.h>
#include"Components.h"
#include<fstream>

namespace YAML
{
	YAML::Emitter& operator << (YAML::Emitter& out, const DM::Vector3& v) {
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}
	YAML::Emitter& operator << (YAML::Emitter& out, const DM::Vector4 v) {
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w<<YAML::EndSeq;
		return out;
	}
	template<>
	struct convert<DM::Vector3>
	{
		static bool decode(const Node& node, DM::Vector3& vec)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			vec.x = node[0].as<float>();
			vec.y = node[1].as<float>();
			vec.z = node[2].as<float>();

			return true;
		}

		static Node encode(const DM::Vector3& vec)
		{
			Node node;
			node.push_back(vec.x);
			node.push_back(vec.y);
			node.push_back(vec.z);
			node.SetStyle(YAML::EmitterStyle::Flow);
			return node;
		}
	};


	template<>
	struct convert<DM::Vector4>
	{
		static bool decode(const Node& node, DM::Vector4& vec)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;
			vec.x = node[0].as<float>();
			vec.y = node[1].as<float>();
			vec.z = node[2].as<float>();
			vec.w = node[3].as<float>();
			return true;
		}

		static Node encode(const DM::Vector4& vec)
		{
			Node node;
			node.push_back(vec.x);
			node.push_back(vec.y);
			node.push_back(vec.z);
			node.push_back(vec.w);
			node.SetStyle(YAML::EmitterStyle::Flow);
			return node;
		}
	};
}

namespace DM
{
	namespace fs = std::filesystem;
	SceneSerializer::SceneSerializer(Ref<Scene>scene):
		m_Context(scene)
	{

	}

	static void SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		out << YAML::BeginMap; 
		{
			out << YAML::Key << "ID" << YAML::Value << 11111111111;
			out << YAML::Key << "Components" << YAML::Value;
			out << YAML::BeginMap; 
			{
				if (entity.HasComponent<TagComponent>())
				{
					auto& com = entity.GetComponent<TagComponent>();
					out << YAML::Key << "TagComponent" << YAML::Value;
					out << YAML::BeginMap; 
					{
						out << YAML::Key << "Tag" << YAML::Value << com.Tag; 
					}
					out << YAML::EndMap;
				}

				if (entity.HasComponent<SpriteComponent>())
				{
					auto& com = entity.GetComponent<SpriteComponent>();
					out << YAML::Key << "SpriteComponent" << YAML::Value;
					out << YAML::BeginMap; 
					{
						out << YAML::Key << "Color" << YAML::Value<<com.Color;
					}
					out << YAML::EndMap;
				}

				if (entity.HasComponent<TransformComponent>())
				{
					auto& com = entity.GetComponent<TransformComponent>();
					out << YAML::Key << "TransformComponent" << YAML::Value;
					out << YAML::BeginMap; 
					{
						out << YAML::Key << "Location" << YAML::Value<< com.Location;

						out << YAML::Key << "Rotation" << YAML::Value<< com.Rotation;

						out << YAML::Key << "Scale" << YAML::Value<< com.Scale;
					}
					out << YAML::EndMap;
				}
			}
			out << YAML::EndMap; 
		}
		out << YAML::EndMap; 
	}

	void SceneSerializer::Serialize(const std::string& filepath)
	{
		fs::path pa(filepath);
		if (!(fs::exists(pa) && fs::is_regular_file(pa)))
		{
			DM_CORE_ASSERT(false, "{} is invalid path!", filepath);
		}
		YAML::Emitter out;
		out.SetIndent(4);
		out << YAML::BeginMap;
		{
			out << YAML::Key << "Scene" << YAML::Value << "Unnamed Scene";
			out << YAML::Key << "Entities" << YAML::Value;
			out << YAML::BeginSeq;
			{
				auto & view=m_Context->m_Registry.view<entt::entity>();
				for (auto& entity : view)
				{
						if (!m_Context->m_Registry.valid(entity))continue;
						Entity en{ entity,m_Context.get() };
						SerializeEntity(out, en);
				}
			}
			out << YAML::EndSeq;
		}
		out << YAML::EndMap;
		std::ofstream outfile(filepath);
		outfile << out.c_str();
	}
	void SceneSerializer::DeSerialize(const std::string& filepath)
	{
		YAML::Node node = YAML::LoadFile(filepath);
		if (!node["Scene"])return;
		const std::string& sceneName = node["Scene"].as<std::string>();
		YAML::Node entities = node["Entities"];
		if (!entities.IsSequence())
		{
			std::cerr << "Error: 'Entities' node is not a sequence (invalid YAML format)." << std::endl;
			return;
		}

		if (entities)
		{
			for (YAML::Node entity : entities)
			{
				auto en=m_Context->CreateEntity();	
				YAML::Node components = entity["Components"];
				if (YAML::Node com = components["TagComponent"])
				{
					en.GetComponent<TagComponent>().Tag = com["Tag"].as<std::string>();
				}
				if (YAML::Node com = components["SpriteComponent"])
				{
					en.GetComponent<SpriteComponent>().Color = com["Color"].as<Vector4>();
				}
				if (YAML::Node com = components["TransformComponent"])
				{
					en.GetComponent<TransformComponent>().Location = com["Location"].as<Vector3>();
					en.GetComponent<TransformComponent>().Rotation = com["Rotation"].as<Vector3>();
					en.GetComponent<TransformComponent>().Scale = com["Scale"].as<Vector3>();
				}
			}
		}
	}
}

