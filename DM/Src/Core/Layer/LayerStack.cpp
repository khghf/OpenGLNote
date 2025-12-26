#include "DMPCH.h"
#include "LayerStack.h"
namespace DM
{
	LayerStack::LayerStack()
	{
		m_LayerInsert = 0;
	}
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			if (layer) 
			{
				layer->OnDetach();
				delete layer;
			}
		}
		m_Layers.clear();
		m_LayerInsert = 0;
	}
	void LayerStack::PushLayer(Layer* layer)
	{
		if (!layer) return; 
		m_Layers.emplace(m_Layers.begin()+m_LayerInsert, layer);
		++m_LayerInsert; 
		layer->OnAttach();
	}
	void LayerStack::PushOverLayer(Layer* layer)
	{
		if (!layer) return;
		m_Layers.emplace_back(layer);
		layer->OnAttach();
	}
	void LayerStack::PopLayer(Layer* layer)
	{
		if (!layer || m_Layers.empty()) return;
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			layer->OnDetach();
			m_Layers.erase(it);
			--m_LayerInsert;
			delete layer;
		}
	}
	void LayerStack::PopOverlay(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer); 
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			layer->OnDetach();
		}
	}
	void LayerStack::Update(float DeletaTime)
	{
		/*for (int i = m_Layers.size() - 1; i >= 0; --i)
		{
			m_Layers[i]->OnUpdate(DeletaTime);
		}*/
		for (const auto layer : m_Layers)
		{
			layer->OnUpdate(DeletaTime);
		}
	}
}