#include "Layer.h"
#include "..\Object\Object.h"

Layer::Layer() :
	m_pScene(nullptr), m_tag(""), m_zOrder(0), m_isEnabled(true), m_isAlive(true)
{
}

Layer::~Layer()
{
	list<Object *>::iterator iter;
	list<Object *>::iterator iterEnd = m_listObject.end();

	for (iter = m_listObject.begin(); iter != iterEnd; ++iter)
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
	list<Object *>::iterator iter;
	list<Object *>::iterator iterEnd = m_listObject.end();

	for (iter = m_listObject.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetEnable())
			continue;

		(*iter)->Input(deltaTime);

		if (!(*iter)->IsAlive())
		{
			Object::EraseObject(*iter);
			SAFE_RELEASE(*iter);
			iter = m_listObject.erase(iter);
			iterEnd = m_listObject.end();
			--iter;
		}
	}
}

int Layer::Update(float deltaTime)
{
	list<Object *>::iterator iter;
	list<Object *>::iterator iterEnd = m_listObject.end();

	for (iter = m_listObject.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetEnable())
			continue;

		(*iter)->Update(deltaTime);

		if (!(*iter)->IsAlive())
		{
			Object::EraseObject(*iter);
			SAFE_RELEASE(*iter);
			iter = m_listObject.erase(iter);
			iterEnd = m_listObject.end();
			--iter;
		}
	}

	return 0;
}

int Layer::LateUpdate(float deltaTime)
{
	list<Object *>::iterator iter;
	list<Object *>::iterator iterEnd = m_listObject.end();

	for (iter = m_listObject.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetEnable())
			continue;

		(*iter)->LateUpdate(deltaTime);

		if (!(*iter)->IsAlive())
		{
			Object::EraseObject(*iter);
			SAFE_RELEASE(*iter);
			iter = m_listObject.erase(iter);
			iterEnd = m_listObject.end();
			--iter;
		}
	}

	return 0;
}

void Layer::Collision(float deltaTime)
{
	list<Object *>::iterator iter;
	list<Object *>::iterator iterEnd = m_listObject.end();

	for (iter = m_listObject.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetEnable())
			continue;

		(*iter)->Collision(deltaTime);

		if (!(*iter)->IsAlive())
		{
			Object::EraseObject(*iter);
			SAFE_RELEASE(*iter);
			iter = m_listObject.erase(iter);
			iterEnd = m_listObject.end();
			--iter;
		}
	}
}

void Layer::Render(HDC hDC, float deltaTime)
{
	list<Object *>::iterator iter;
	list<Object *>::iterator iterEnd = m_listObject.end();

	for (iter = m_listObject.begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetEnable())
			continue;

		(*iter)->Render(hDC, deltaTime);

		if (!(*iter)->IsAlive())
		{
			Object::EraseObject(*iter);
			SAFE_RELEASE(*iter);
			iter = m_listObject.erase(iter);
			iterEnd = m_listObject.end();
			--iter;
		}
	}
}
