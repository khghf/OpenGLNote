#pragma once
namespace DM { class Layer; }
#include"Layer.h"
#include"../Container/Array.h"
namespace DM
{
	//管理游戏中的不同分层
	class DM_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);
		void Update(float DeletaTime);
		Array<Layer*>::iterator begin() { return m_Layers.begin(); }
		Array<Layer*>::iterator end() { return m_Layers.end(); }
		int Size()const { return m_Layers.size();}
	private:
		Array<Layer*>m_Layers;
		int m_LayerInsert;
	};
}


