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

void Scene::Input(float deltaTime)
{
	list<Layer *>::iterator iter;
	list<Layer *>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Input(deltaTime);
	}
}

int Scene::Update(float deltaTime)
{
	list<Layer *>::iterator iter;
	list<Layer *>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Update(deltaTime);
	}

	return 0;
}

int Scene::LateUpdate(float deltaTime)
{
	list<Layer *>::iterator iter;
	list<Layer *>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->LateUpdate(deltaTime);
	}

	return 0;
}

void Scene::Collision(float deltaTime)
{
	list<Layer *>::iterator iter;
	list<Layer *>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Collision(deltaTime);
	}
}

void Scene::Render(HDC hDC, float deltaTime)
{
	list<Layer *>::iterator iter;
	list<Layer *>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Render(hDC, deltaTime);
	}
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

Layer * Scene::FindLayer(const string & tag)
{
	list<Layer *>::iterator iter;
	list<Layer *>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == tag)
			return *iter;
	}

	return nullptr;
}
