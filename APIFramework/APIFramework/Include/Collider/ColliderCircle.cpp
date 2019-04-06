#include "ColliderCircle.h"
#include "..\Object\Object.h"
#include "ColliderRect.h"
#include "ColliderPixel.h"

ColliderCircle::ColliderCircle()
{
	m_type = CT_CIRCLE;
}

ColliderCircle::ColliderCircle(const ColliderCircle & collider) :
	Collider(collider)
{
	m_circle = collider.m_circle;
}

ColliderCircle::~ColliderCircle()
{
}

bool ColliderCircle::Init()
{
	return true;
}

void ColliderCircle::Input(float deltaTime)
{
	Collider::Input(deltaTime);
}

int ColliderCircle::Update(float deltaTime)
{
	Collider::Update(deltaTime);

	return 0;
}

int ColliderCircle::LateUpdate(float deltaTime)
{
	Collider::LateUpdate(deltaTime);

	POSITION pos = m_pObj->GetPos();
	m_circleWorld.p = pos + m_circle.p;
	m_circleWorld.r = m_circle.r;

	return 0;
}

bool ColliderCircle::Collision(Collider * pDest)
{
	switch (pDest->GetType())
	{
	case CT_CIRCLE:
		return CollisionCircleVsCircle(m_circleWorld, ((ColliderCircle*)pDest)->GetCircleWorld());
		break;
	case CT_RECT:
		return CollisionRectVsCircle(((ColliderRect*)pDest)->GetRectWorld(), m_circleWorld);
		break;
	}

	return false;
}

void ColliderCircle::Render(HDC hDC, float deltaTime)
{
	Collider::Render(hDC, deltaTime);
}

ColliderCircle * ColliderCircle::Clone()
{
	return new ColliderCircle(*this);
}
