#pragma once
#include "..\Game.h"

class Scene
{
protected:

	list<class Layer *> m_LayerList;

	friend class SceneManager;

	Scene();
	virtual ~Scene() = 0;  // 순수 가상 함수 (=> 추상 클래스)

public:

	static bool LayerSort(class Layer * pL1, class Layer * pL2);

	virtual bool Init();
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual void Collision(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);

	class Layer * CreateLayer(const string & tag, int zOrder = 0);
	class Layer * FindLayer(const string & tag);
};
