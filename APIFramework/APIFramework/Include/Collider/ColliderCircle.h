#pragma once
#include "Collider.h"

class ColliderCircle : public Collider
{
	CIRCLE m_circle;
	CIRCLE m_circleWorld;

protected:

	friend class Object;

	ColliderCircle();
	ColliderCircle(const ColliderCircle & collider);
	~ColliderCircle();

public:

	void SetCircle(const POSITION & p, float r) { m_circle.p = p; m_circle.r = r; }
	CIRCLE GetCircle() const { return m_circle; }
	CIRCLE GetCircleWorld() const { return m_circleWorld; }

	virtual bool Init();
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual bool Collision(Collider * pDest);
	virtual void Render(HDC hDC, float deltaTime);
	virtual ColliderCircle * Clone();
};
