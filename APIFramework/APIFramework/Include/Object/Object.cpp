#include "Object.h"
#include "..\Resource\ResourceManager.h"
#include "..\Resource\Texture.h"
#include "..\Scene\SceneManager.h"
#include "..\Scene\Scene.h"
#include "..\Scene\Layer.h"
#include "..\Collider\Collider.h"

list<Object *> Object::m_listObject;

Object::Object() :
	m_pTexture(nullptr), m_pivot(0.5f, 0.5f), m_hasPhysics(false), m_gravityTime(0.f)
{
}

Object::Object(const Object & obj)
{
	*this = obj;

	m_gravityTime = 0.f;

	if (m_pTexture)
		m_pTexture->AddRef();

	m_listCollider.clear();

	for (list<Collider *>::const_iterator iter = obj.m_listCollider.begin(); iter != obj.m_listCollider.end(); ++iter)
	{
		Collider * pCollider = (*iter)->Clone();
		pCollider->SetObj(this);

		m_listCollider.push_back(pCollider);
	}
}

Object::~Object()
{
	SAFE_RELEASE(m_pTexture);
	SafeReleaseVectorList(m_listCollider);
}

Object * Object::CloneObject(const string & key, const string & tag, class Layer * pLayer)
{
	Object * pPrototype = Scene::FindPrototype(key);

	if (!pPrototype)
		return nullptr;

	Object * pObj = pPrototype->Clone();

	pObj->SetTag(tag);

	if (pLayer)
		pLayer->AddObject(pObj);

	pObj->AddRef();
	m_listObject.push_back(pObj);

	return pObj;
}

Object * Object::FindObject(const string & tag)
{
	for (list<Object *>::iterator iter = m_listObject.begin(); iter != m_listObject.end(); ++iter)
	{
		if ((*iter)->GetTag() == tag)
		{
			(*iter)->AddRef();
			return *iter;
		}
	}

	return nullptr;
}

void Object::EraseObject(Object * pObj)
{
	for (list<Object *>::iterator iter = m_listObject.begin(); iter != m_listObject.end(); ++iter)
	{
		if (*iter == pObj)
		{
			SAFE_RELEASE(*iter);
			iter = m_listObject.erase(iter);
			return;
		}
	}
}

void Object::EraseObject(const string & tag)
{
	for (list<Object *>::iterator iter = m_listObject.begin(); iter != m_listObject.end(); ++iter)
	{
		if ((*iter)->GetTag() == tag)
		{
			SAFE_RELEASE(*iter);
			iter = m_listObject.erase(iter);
			return;
		}
	}
}

void Object::ClearObjects()
{
	SafeReleaseVectorList(m_listObject);
}

void Object::SetTexture(Texture * pTexture)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = pTexture;

	if (pTexture)
		pTexture->AddRef();
}

void Object::SetTexture(const string & key, const wchar_t * pFileName, const string & pathKey)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = GET_SINGLE(ResourceManager)->LoadTexture(key, pFileName, pathKey);
}

bool Object::Init()
{
	return true;
}

void Object::Input(float deltaTime)
{
}

int Object::Update(float deltaTime)
{
	if (m_hasPhysics)
	{
		m_gravityTime += deltaTime;
		m_pos.y += (GRAVITY * m_gravityTime * m_gravityTime);
	}

	for (list<Collider *>::iterator iter = m_listCollider.begin(); iter != m_listCollider.end(); ++iter)
	{
		if (!(*iter)->IsEnabled())
			continue;

		if (!(*iter)->IsAlive())
		{
			SAFE_RELEASE(*iter);
			iter = m_listCollider.erase(iter);
			--iter;
			continue;
		}

		(*iter)->Update(deltaTime);
	}

	return 0;
}

int Object::LateUpdate(float deltaTime)
{
	for (list<Collider *>::iterator iter = m_listCollider.begin(); iter != m_listCollider.end(); ++iter)
	{
		if (!(*iter)->IsEnabled())
			continue;

		if (!(*iter)->IsAlive())
		{
			SAFE_RELEASE(*iter);
			iter = m_listCollider.erase(iter);
			--iter;
			continue;
		}

		(*iter)->LateUpdate(deltaTime);
	}

	return 0;
}

void Object::Collision(float deltaTime)
{
}

void Object::Render(HDC hDC, float deltaTime)
{
	if (m_pTexture)
	{
		POSITION pos = m_pos - m_size * m_pivot;
		int pX = (int)pos.x, pY = (int)pos.y, sX = (int)m_size.x, sY = (int)m_size.y;

		if (m_pTexture->HasColorKey())
		{
			TransparentBlt(hDC, pX, pY, sX, sY, m_pTexture->GetDC(), 0, 0, sX, sY, m_pTexture->GetColorKey());
		}
		else
		{
			BitBlt(hDC, pX, pY, sX, sY, m_pTexture->GetDC(), 0, 0, SRCCOPY);
		}
	}

	// Ãæµ¹Ã¼ ·»´õ
	for (list<Collider *>::iterator iter = m_listCollider.begin(); iter != m_listCollider.end(); ++iter)
	{
		if (!(*iter)->IsEnabled())
			continue;

		if (!(*iter)->IsAlive())
		{
			SAFE_RELEASE(*iter);
			iter = m_listCollider.erase(iter);
		}

		(*iter)->Render(hDC, deltaTime);
	}
}
