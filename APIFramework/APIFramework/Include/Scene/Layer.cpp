#include "Layer.h"
#include "..\Object\Object.h"

Layer::Layer() :
	m_pScene(nullptr), m_tag(""), m_zOrder(0)
{
}

Layer::~Layer()
{
	SafeReleaseVectorList(m_ObjectList);
}

void Layer::AddObject(Object * pObj)
{
	m_ObjectList.push_back(pObj);
	pObj->SetScene(m_pScene);
	pObj->SetLayer(this);
	pObj->AddRef();
}

void Layer::Input(float deltaTime)
{
	list<Object *>::iterator iter;
	list<Object *>::iterator iterEnd = m_ObjectList.end();

	for (iter = m_ObjectList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Input(deltaTime);
	}
}

int Layer::Update(float deltaTime)
{
	list<Object *>::iterator iter;
	list<Object *>::iterator iterEnd = m_ObjectList.end();

	for (iter = m_ObjectList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Update(deltaTime);
	}

	return 0;
}

int Layer::LateUpdate(float deltaTime)
{
	list<Object *>::iterator iter;
	list<Object *>::iterator iterEnd = m_ObjectList.end();

	for (iter = m_ObjectList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->LateUpdate(deltaTime);
	}

	return 0;
}

void Layer::Collision(float deltaTime)
{
	list<Object *>::iterator iter;
	list<Object *>::iterator iterEnd = m_ObjectList.end();

	for (iter = m_ObjectList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Collision(deltaTime);
	}
}

void Layer::Render(HDC hDC, float deltaTime)
{
	list<Object *>::iterator iter;
	list<Object *>::iterator iterEnd = m_ObjectList.end();

	for (iter = m_ObjectList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Render(hDC, deltaTime);
	}
}
