#pragma once
namespace DM { class Layer; }
#include"Layer.h"
namespace DM
{
	//管理游戏中的不同分层
	class  LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);
		void Update(float DeletaTime);
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		size_t Size()const { return m_Layers.size();}
	private:
		std::vector<Layer*>m_Layers;
		int m_LayerInsert;
	};
}


