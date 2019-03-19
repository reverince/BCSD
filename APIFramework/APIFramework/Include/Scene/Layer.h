#pragma once
#include "..\Game.h"

class Layer
{
	class Scene * m_pScene;
	string m_tag;
	int m_zOrder;

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
};
