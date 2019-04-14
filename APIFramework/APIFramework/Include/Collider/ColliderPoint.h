#pragma once
#include "Collider.h"

class ColliderPoint : public Collider
{
	POSITION m_pos;
	POSITION m_dist;

protected:

	friend class Object;

	ColliderPoint();
	ColliderPoint(const ColliderPoint& coll);
	~ColliderPoint();

public:

	void SetDist(const POSITION& dist) { m_dist = dist; }
	void SetDist(float x, float y) { m_dist = POSITION(x, y); }
	POSITION GetPos() const { return m_pos; }

	virtual bool Init();
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual bool Collision(Collider* pDest);
	virtual void Render(HDC hDC, float deltaTime);
	virtual ColliderPoint* Clone();
};

