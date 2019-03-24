#include "Layer.h"
#include "..\Object\Object.h"
#include "..\Collider\CollisionManager.h"

Layer::Layer() :
	m_pScene(nullptr), m_tag(""), m_zOrder(0), m_isEnabled(true), m_isAlive(true)
{
}

Layer::~Layer()
{
	for (list<Object *>::iterator iter = m_listObject.begin(); iter != m_listObject.end(); ++iter)
	{
		// 오브젝트 제거
		Object::EraseObject(*iter);
		SAFE_RELEASE(*iter);
	}

	m_listObject.clear();
}

void Layer::AddObject(Object * pObj)
{
	pObj->SetScene(m_pScene);
	pObj->SetLayer(this);
	pObj->AddRef();
	m_listObject.push_back(pObj);
}

void Layer::Input(float deltaTime)
{
	for (list<Object *>::iterator iter = m_listObject.begin(); iter != m_listObject.end(); ++iter)
	{
		if (!(*iter)->GetEnabled())
			continue;

		if (!(*iter)->IsAlive())
		{
			Object::EraseObject(*iter);
			SAFE_RELEASE(*iter);
			iter = m_listObject.erase(iter);
			--iter;
			continue;
		}

		(*iter)->Input(deltaTime);
	}
}

int Layer::Update(float deltaTime)
{
	for (list<Object *>::iterator iter = m_listObject.begin(); iter != m_listObject.end(); ++iter)
	{
		if (!(*iter)->GetEnabled())
			continue;

		if (!(*iter)->IsAlive())
		{
			Object::EraseObject(*iter);
			SAFE_RELEASE(*iter);
			iter = m_listObject.erase(iter);
			--iter;
			continue;
		}

		(*iter)->Update(deltaTime);
	}

	return 0;
}

int Layer::LateUpdate(float deltaTime)
{
	for (list<Object *>::iterator iter = m_listObject.begin(); iter != m_listObject.end(); ++iter)
	{
		if (!(*iter)->GetEnabled())
			continue;

		if (!(*iter)->IsAlive())
		{
			Object::EraseObject(*iter);
			SAFE_RELEASE(*iter);
			iter = m_listObject.erase(iter);
			--iter;
			continue;
		}

		(*iter)->LateUpdate(deltaTime);
	}

	return 0;
}

void Layer::Collision(float deltaTime)
{
	for (list<Object *>::iterator iter = m_listObject.begin(); iter != m_listObject.end(); ++iter)
	{
		if (!(*iter)->GetEnabled())
			continue;

		if (!(*iter)->IsAlive())
		{
			Object::EraseObject(*iter);
			SAFE_RELEASE(*iter);
			iter = m_listObject.erase(iter);
			--iter;
			continue;
		}

		GET_SINGLE(CollisionManager)->AddObject(*iter);

		(*iter)->Collision(deltaTime);
	}
}

void Layer::Render(HDC hDC, float deltaTime)
{
	for (list<Object *>::iterator iter = m_listObject.begin(); iter != m_listObject.end(); ++iter)
	{
		if (!(*iter)->GetEnabled())
			continue;

		if (!(*iter)->IsAlive())
		{
			Object::EraseObject(*iter);
			SAFE_RELEASE(*iter);
			iter = m_listObject.erase(iter);
			--iter;
			continue;
		}

		(*iter)->Render(hDC, deltaTime);
	}
}
