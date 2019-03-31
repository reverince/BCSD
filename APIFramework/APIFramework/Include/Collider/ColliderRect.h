#pragma once
#include "Collider.h"

class ColliderRect : public Collider
{
	RECTANGLE m_rect;
	RECTANGLE m_rectWorld;

protected:

	friend class Object;

	ColliderRect();
	ColliderRect(const ColliderRect & collider);
	virtual ~ColliderRect();

public:

	void SetRect(float l, float t, float r, float b) { m_rect = RECTANGLE(l, t, r, b); }
	RECTANGLE GetRect() const { return m_rect; }
	RECTANGLE GetRectWorld() const { return m_rectWorld; }

	virtual bool Init();
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual bool Collision(Collider * pDest);
	virtual void Render(HDC hDC, float deltaTime);
	virtual ColliderRect * Clone();
};
