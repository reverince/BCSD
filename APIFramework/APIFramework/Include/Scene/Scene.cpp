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
	list<Layer *>::iterator iter;
	list<Layer *>::iterator iterEnd = m_listLayer.end();

	for (iter = m_listLayer.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetEnable())
			continue;

		(*iter)->Input(deltaTime);

		if (!(*iter)->IsAlive())
		{
			SAFE_DELETE(*iter);
			iter = m_listLayer.erase(iter);
			iterEnd = m_listLayer.end();
			--iter;
		}
	}
}

int Scene::Update(float deltaTime)
{
	list<Layer *>::iterator iter;
	list<Layer *>::iterator iterEnd = m_listLayer.end();

	for (iter = m_listLayer.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetEnable())
			continue;

		(*iter)->Update(deltaTime);

		if (!(*iter)->IsAlive())
		{
			SAFE_DELETE(*iter);
			iter = m_listLayer.erase(iter);
			iterEnd = m_listLayer.end();
			--iter;
		}
	}

	return 0;
}

int Scene::LateUpdate(float deltaTime)
{
	list<Layer *>::iterator iter;
	list<Layer *>::iterator iterEnd = m_listLayer.end();

	for (iter = m_listLayer.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetEnable())
			continue;

		(*iter)->LateUpdate(deltaTime);

		if (!(*iter)->IsAlive())
		{
			SAFE_DELETE(*iter);
			iter = m_listLayer.erase(iter);
			iterEnd = m_listLayer.end();
			--iter;
		}
	}

	return 0;
}

void Scene::Collision(float deltaTime)
{
	list<Layer *>::iterator iter;
	list<Layer *>::iterator iterEnd = m_listLayer.end();

	for (iter = m_listLayer.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetEnable())
			continue;

		(*iter)->Collision(deltaTime);

		if (!(*iter)->IsAlive())
		{
			SAFE_DELETE(*iter);
			iter = m_listLayer.erase(iter);
			iterEnd = m_listLayer.end();
			--iter;
		}
	}
}

void Scene::Render(HDC hDC, float deltaTime)
{
	list<Layer *>::iterator iter;
	list<Layer *>::iterator iterEnd = m_listLayer.end();

	for (iter = m_listLayer.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetEnable())
			continue;

		(*iter)->Render(hDC, deltaTime);

		if (!(*iter)->IsAlive())
		{
			SAFE_DELETE(*iter);
			iter = m_listLayer.erase(iter);
			iterEnd = m_listLayer.end();
			--iter;
		}
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
	list<Layer *>::iterator iter;
	list<Layer *>::iterator iterEnd = m_listLayer.end();

	for (iter = m_listLayer.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == tag)
			return *iter;
	}

	return nullptr;
}
