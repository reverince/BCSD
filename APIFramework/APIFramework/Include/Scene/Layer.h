#pragma once
#include "..\Game.h"

class Layer
{
	class Scene * m_pScene;
	string m_tag;
	int m_zOrder;
	bool m_isEnabled;
	bool m_isAlive;
	list<class Object *> m_listObject;

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

	void SetEnabled(bool enable) { m_isEnabled = enable; }
	bool IsEnabled() const { return m_isEnabled; }
	void Die() { m_isAlive = false; }
	bool IsAlive() const { return m_isAlive; }

	void AddObject(Object * pObj);

	void Input(float deltaTime);
	int Update(float deltaTime);
	int LateUpdate(float deltaTime);
	void Collision(float deltaTime);
	void Render(HDC hDC, float deltaTime);
};
