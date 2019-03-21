#pragma once
#include "..\Reference.h"
#include "..\Scene\Layer.h"

class Object : public Reference
{
	static list<Object *> m_listObject;

protected:
	
	friend class Scene;

	class Scene * m_pScene;
	class Layer * m_pLayer;

	string m_tag;
	POSITION m_pos;
	_SIZE m_size;
	POSITION m_pivot;

	Object();
	Object(const Object & obj);
	virtual ~Object();
	
public:

	template <typename T>
	static T * CreateObject(const string & tag, class Layer * pLayer = nullptr)
	{
		T * pObj = new T;

		pObj->SetTag(tag);

		if (!pObj->Init())
		{
			SAFE_RELEASE(pObj);
			return nullptr;
		}

		if (pLayer)
			pLayer->AddObject(pObj);

		pObj->AddRef();
		m_listObject.push_back(pObj);

		return pObj;
	}

	static Object * CloneObject(const string & key, const string & tag, class Layer * pLayer = nullptr);
	
	static Object * FindObject(const string & tag);
	static void EraseObject(Object * pObj);
	static void EraseObject(const string & tag);
	static void ClearObjects();

	void SetScene(class Scene * pScene) { m_pScene = pScene; }
	void SetLayer(class Layer * pLayer) { m_pLayer = pLayer; }
	class Scene * GetScene() const { return m_pScene; }
	class Layer * GetLayer() const { return m_pLayer; }

	void SetTag(string tag) { m_tag = tag; }
	void SetPos(const POSITION & pos) { m_pos = pos; }
	void SetPos(const POINT & pt) { m_pos = pt; }
	void SetPos(float x, float y) { m_pos.x = x; m_pos.y = y; }
	void SetSize(const POSITION & size) { m_size = size; }
	void SetSize(const POINT & pt) { m_size = pt; }
	void SetSize(float x, float y) { m_size.x = x; m_size.y = y; }
	string GetTag() const { return m_tag; }
	POSITION GetPos() const { return m_pos; }
	_SIZE GetSize() const { return m_size; }

	virtual bool Init();
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual void Collision(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	virtual Object * Clone() = 0;
};
