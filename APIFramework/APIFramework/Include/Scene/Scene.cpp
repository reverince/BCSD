#include "Scene.h"
#include "Layer.h"

Scene::Scene()
{
	Layer * pLayer = CreateLayer("Default");
	pLayer = CreateLayer("UI", INT_MAX);
}

Scene::~Scene()
{
	SafeDeleteVectorList(m_LayerList);
}

// Layer를 zOrder 기준 오름차순 정렬
bool Scene::LayerSort(Layer * pL1, Layer * pL2)
{
	return pL1->GetZOrder() < pL2->GetZOrder();
}

bool Scene::Init()
{
	return true;
}

Layer * Scene::CreateLayer(const string & tag, int zOrder)
{
	Layer * pLayer = new Layer;

	pLayer->SetScene(this);
	pLayer->SetTag(tag);
	pLayer->SetZOrder(zOrder);

	m_LayerList.push_back(pLayer);

	if (m_LayerList.size() > 1)
		m_LayerList.sort(Scene::LayerSort);

	return pLayer;
}
