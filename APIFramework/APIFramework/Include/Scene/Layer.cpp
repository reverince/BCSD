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
	for (list<Object *>::iterator iter = m_listObject.begin(); iter != m_listObject.end();)
	{
		if (!(*iter)->IsEnabled())
		{
			++iter;
			continue;
		}

		(*iter)->Input(deltaTime);

		if (!(*iter)->IsAlive())
		{
			Object::EraseObject(*iter);
			SAFE_RELEASE(*iter);
			iter = m_listObject.erase(iter);
		}
		else
			++iter;
	}
}

int Layer::Update(float deltaTime)
{
	for (list<Object *>::iterator iter = m_listObject.begin(); iter != m_listObject.end();)
	{
		if (!(*iter)->IsEnabled())
		{
			++iter;
			continue;
		}

		(*iter)->Update(deltaTime);

		if (!(*iter)->IsAlive())
		{
			Object::EraseObject(*iter);
			SAFE_RELEASE(*iter);
			iter = m_listObject.erase(iter);
		}
		else
			++iter;
	}

	return 0;
}

int Layer::LateUpdate(float deltaTime)
{
	for (list<Object *>::iterator iter = m_listObject.begin(); iter != m_listObject.end();)
	{
		if (!(*iter)->IsEnabled())
		{
			++iter;
			continue;
		}

		(*iter)->LateUpdate(deltaTime);

		if (!(*iter)->IsAlive())
		{
			Object::EraseObject(*iter);
			SAFE_RELEASE(*iter);
			iter = m_listObject.erase(iter);
		}
		else
			++iter;
	}

	return 0;
}

void Layer::Collision(float deltaTime)
{
	for (list<Object *>::iterator iter = m_listObject.begin(); iter != m_listObject.end();)
	{
		if (!(*iter)->IsEnabled())
		{
			++iter;
			continue;
		}

		(*iter)->Collision(deltaTime);

		if (!(*iter)->IsAlive())
		{
			Object::EraseObject(*iter);
			SAFE_RELEASE(*iter);
			iter = m_listObject.erase(iter);
		}
		else
		{
			GET_SINGLE(CollisionManager)->AddObject(*iter);
			++iter;
		}
	}
}

void Layer::Render(HDC hDC, float deltaTime)
{
	for (list<Object *>::iterator iter = m_listObject.begin(); iter != m_listObject.end();)
	{
		if (!(*iter)->IsEnabled())
		{
			iter++;
			continue;
		}

		(*iter)->Render(hDC, deltaTime);

		if (!(*iter)->IsAlive())
		{
			Object::EraseObject(*iter);
			SAFE_RELEASE(*iter);
			iter = m_listObject.erase(iter);
		}
		else
			++iter;
	}
}
