#include "Object.h"
#include "..\Scene\SceneManager.h"
#include "..\Scene\Scene.h"
#include "..\Scene\Layer.h"

list<Object *> Object::m_listObject;

Object::Object()
{
}

Object::Object(const Object & obj)
{
	*this = obj;
}

Object::~Object()
{
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
	list<Object *>::iterator iter;
	list<Object *>::iterator iterEnd = m_listObject.end();

	for (iter = m_listObject.begin(); iter != iterEnd; ++iter)
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
	list<Object *>::iterator iter;
	list<Object *>::iterator iterEnd = m_listObject.end();

	for (iter = m_listObject.begin(); iter != iterEnd; ++iter)
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
	list<Object *>::iterator iter;
	list<Object *>::iterator iterEnd = m_listObject.end();

	for (iter = m_listObject.begin(); iter != iterEnd; ++iter)
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

bool Object::Init()
{
	return true;
}

void Object::Input(float deltaTime)
{
}

int Object::Update(float deltaTime)
{
	return 0;
}

int Object::LateUpdate(float deltaTime)
{
	return 0;
}

void Object::Collision(float deltaTime)
{
}

void Object::Render(HDC hDC, float deltaTime)
{
}
