#pragma once
#include "..\Reference.h"
#include "..\Scene\Layer.h"
#include "..\Resource\Texture.h"
#include "..\Collider\Collider.h"

class Object : public Reference
{
	static list<Object *> m_listObject;

protected:

	friend class Scene;

	class Scene * m_pScene;
	class Layer * m_pLayer;
	class Texture * m_pTexture;
	list<Collider *> m_listCollider;
	class Animation * m_pAnimation;

	string m_tag;
	POSITION m_pos;
	_SIZE m_size;
	POSITION m_pivot;
	bool m_hasPhysics;
	float m_gravityTime;

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
	void SetPivot(const POSITION & size) { m_pivot = size; }
	void SetPivot(float x, float y) { m_pivot.x = x; m_pivot.y = y; }
	void SetSize(const POSITION & size) { m_size = size; }
	void SetSize(const POINT & pt) { m_size = pt; }
	void SetSize(float x, float y) { m_size.x = x; m_size.y = y; }
	string GetTag() const { return m_tag; }
	POSITION GetPos() const { return m_pos; }
	_SIZE GetSize() const { return m_size; }
	POSITION GetPivot() const { return m_pivot; }

	void SetPhysics(bool hasPhysics) { m_hasPhysics = hasPhysics; }
	bool GetPhysics() const { return m_hasPhysics; }

	void SetTexture(class Texture * pTexture);
	void SetTexture(const string & key, const wchar_t * pFileName = nullptr, const string & pathKey = PATH_TEXTURE);

	void SetColorKey(UCHAR r, UCHAR g, UCHAR b) { m_pTexture->SetColorKey(r, g, b); }

	template <typename T>
	void AddCollisionFunc(const string & tag, COLLISION_STATE state, T * pObj, void(T::*pFunc)(float, Collider *, Collider *))
	{
		for (list<Collider *>::iterator iter = m_listCollider.begin(); iter != m_listCollider.end(); ++iter)
		{
			if ((*iter)->GetTag() == tag)
			{
				(*iter)->AddCollisionFunc(state, pObj, pFunc);
				break;
			}
		}
	}

	template <typename T>
	T * AddCollider(const string & tag)
	{
		T * pCollider = new T;

		pCollider->SetObj(this);
		pCollider->SetTag(tag);

		if (!pCollider->Init())
		{
			SAFE_RELEASE(pCollider);
			return nullptr;
		}

		pCollider->AddRef();
		m_listCollider.push_back(pCollider);

		return pCollider;
	}
	bool HasCollider() { return !m_listCollider.empty(); }
	const list<Collider *> * GetColliders() const { return &m_listCollider; }

	class Animation * CreateAnimation(const string & tag);
	bool AddAnimationClip(const string & name, ANIMATION_TYPE type, ANIMATION_OPTION option,
		float timeMax, float optionTimeMax,
		int frameMaxX, int frameMaxY, int startX, int startY, int lengthX, int lengthY,
		const string & keyTexture, const wchar_t * pFileName, const string & keyPath = PATH_TEXTURE);
	bool AddAnimationClip(const string & name, ANIMATION_TYPE type, ANIMATION_OPTION option,
		float timeMax, float optionTimeMax,
		int frameMaxX, int frameMaxY, int startX, int startY, int lengthX, int lengthY,
		const string & keyTexture, const vector<wstring> & fileNames, const string & keyPath = PATH_TEXTURE);

	virtual bool Init();
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual void Collision(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	virtual Object * Clone() = 0;
};
