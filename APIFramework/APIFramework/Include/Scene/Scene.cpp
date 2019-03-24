#include "Scene.h"
#include "Layer.h"
#include "..\Object\Object.h"

unordered_map<string, class Object *> Scene::m_mapPrototype;

Scene::Scene()
{
	Layer * pLayer;
	pLayer = CreateLayer("Stage", 0);
	pLayer = CreateLayer("Default", 1);
	pLayer = CreateLayer("UI", INT_MAX);
}

Scene::~Scene()
{
	ClearPrototypes();
	SafeDeleteVectorList(m_listLayer);
}

// Layer를 zOrder 기준 오름차순 정렬
bool Scene::LayerSort(Layer * pL1, Layer * pL2)
{
	return pL1->GetZOrder() < pL2->GetZOrder();
}

Object * Scene::FindPrototype(const string & key)
{
	unordered_map<string, Object *>::iterator iter = m_mapPrototype.find(key);

	if (iter == m_mapPrototype.end())
		return nullptr;

	return iter->second;
}

void Scene::ErasePrototype(const string & key)
{
	unordered_map<string, Object *>::iterator iter = m_mapPrototype.find(key);

	if (!iter->second)
		return;

	SAFE_RELEASE(iter->second);
	m_mapPrototype.erase(iter);
}

void Scene::ClearPrototypes()
{
	SafeReleaseMap(m_mapPrototype);
}

bool Scene::Init()
{
	return true;
}

void Scene::Input(float deltaTime)
{
	for (list<Layer *>::iterator iter = m_listLayer.begin(); iter != m_listLayer.end(); ++iter)
	{
		if (!(*iter)->GetEnabled())
			continue;

		if (!(*iter)->IsAlive())
		{
			SAFE_DELETE(*iter);
			iter = m_listLayer.erase(iter);
			--iter;
		}

		(*iter)->Input(deltaTime);
	}
}

int Scene::Update(float deltaTime)
{
	for (list<Layer *>::iterator iter = m_listLayer.begin(); iter != m_listLayer.end(); ++iter)
	{
		if (!(*iter)->GetEnabled())
			continue;

		if (!(*iter)->IsAlive())
		{
			SAFE_DELETE(*iter);
			iter = m_listLayer.erase(iter);
			--iter;
		}

		(*iter)->Update(deltaTime);
	}

	return 0;
}

int Scene::LateUpdate(float deltaTime)
{
	for (list<Layer *>::iterator iter = m_listLayer.begin(); iter != m_listLayer.end(); ++iter)
	{
		if (!(*iter)->GetEnabled())
			continue;

		if (!(*iter)->IsAlive())
		{
			SAFE_DELETE(*iter);
			iter = m_listLayer.erase(iter);
			--iter;
		}

		(*iter)->LateUpdate(deltaTime);
	}

	return 0;
}

void Scene::Collision(float deltaTime)
{
	for (list<Layer *>::iterator iter = m_listLayer.begin(); iter != m_listLayer.end(); ++iter)
	{
		if (!(*iter)->GetEnabled())
			continue;

		if (!(*iter)->IsAlive())
		{
			SAFE_DELETE(*iter);
			iter = m_listLayer.erase(iter);
			--iter;
		}

		(*iter)->Collision(deltaTime);
	}
}

void Scene::Render(HDC hDC, float deltaTime)
{
	for (list<Layer *>::iterator iter = m_listLayer.begin(); iter != m_listLayer.end(); ++iter)
	{
		if (!(*iter)->GetEnabled())
			continue;

		if (!(*iter)->IsAlive())
		{
			SAFE_DELETE(*iter);
			iter = m_listLayer.erase(iter);
			--iter;
		}

		(*iter)->Render(hDC, deltaTime);
	}
}

Layer * Scene::CreateLayer(const string & tag, int zOrder)
{
	Layer * pLayer = new Layer;

	pLayer->SetScene(this);
	pLayer->SetTag(tag);
	pLayer->SetZOrder(zOrder);

	m_listLayer.push_back(pLayer);

	if (m_listLayer.size() > 1)
		m_listLayer.sort(Scene::LayerSort);

	return pLayer;
}

Layer * Scene::FindLayer(const string & tag)
{
	for (list<Layer *>::iterator iter = m_listLayer.begin(); iter != m_listLayer.end(); ++iter)
	{
		if ((*iter)->GetTag() == tag)
			return *iter;
	}

	return nullptr;
}
