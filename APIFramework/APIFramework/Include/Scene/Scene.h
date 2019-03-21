#pragma once
#include "..\Game.h"

class Scene
{
protected:

	list<class Layer *> m_listLayer;
	static unordered_map<string, class Object *> m_mapPrototype;

	friend class SceneManager;

	Scene();
	virtual ~Scene() = 0;  // 순수 가상 함수 (=> 추상 클래스)

public:

	static bool LayerSort(class Layer * pL1, class Layer * pL2);

	template <typename T>
	static T * CreatePrototype(const string & tag)
	{
		T * pObj = new T;

		pObj->SetTag(tag);

		if (!pObj->Init())
		{
			SAFE_RELEASE(pObj);
			return nullptr;
		}

		pObj->AddRef();
		m_mapPrototype.insert(make_pair(tag, pObj));

		return pObj;
	}

	static Object * FindPrototype(const string & key);
	static void ErasePrototype(const string & tag);
	static void ClearPrototypes();

	virtual bool Init();
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual void Collision(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);

	class Layer * CreateLayer(const string & tag, int zOrder = 0);
	class Layer * FindLayer(const string & tag);
};
