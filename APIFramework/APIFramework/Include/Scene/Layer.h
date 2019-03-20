#pragma once
#include "..\Game.h"

class Layer
{
	class Scene * m_pScene;
	string m_tag;
	int m_zOrder;
	list<class Object *> m_ObjectList;

	friend class Scene;

	Layer();

public:

	~Layer();

	void SetScene(class Scene * pScene) { m_pScene = pScene; }
	void SetTag(const string & tag) { m_tag = tag; }
	void SetZOrder(int zOrder) { m_zOrder = zOrder; }
	Scene * GetScene() const { return m_pScene; }
	string GetTag() const { return m_tag; }
	int GetZOrder() const { return m_zOrder; }

	void AddObject(Object * pObj);

	void Input(float deltaTime);
	int Update(float deltaTime);
	int LateUpdate(float deltaTime);
	void Collision(float deltaTime);
	void Render(HDC hDC, float deltaTime);
};
