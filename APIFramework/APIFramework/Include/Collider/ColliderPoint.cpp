#include "ColliderPoint.h"
#include "..\Object\Object.h"
#include "ColliderRect.h"
#include "ColliderCircle.h"
#include "ColliderPixel.h"

ColliderPoint::ColliderPoint()
{
	m_type = CT_POINT;
}

ColliderPoint::ColliderPoint(const ColliderPoint& coll) :
	Collider(coll)
{
	m_dist = coll.m_dist;
}

ColliderPoint::~ColliderPoint()
{
}

bool ColliderPoint::Init()
{
	return true;
}

void ColliderPoint::Input(float deltaTime)
{
	Collider::Input(deltaTime);
}

int ColliderPoint::Update(float deltaTime)
{
	Collider::Update(deltaTime);

	return 0;
}

int ColliderPoint::LateUpdate(float deltaTime)
{
	Collider::LateUpdate(deltaTime);

	POSITION pos = m_pObj->GetPos();
	m_pos.x = pos.x + m_dist.x;
	m_pos.y = pos.y + m_dist.y;

	return 0;
}

bool ColliderPoint::Collision(Collider* pDest)
{
	switch (pDest->GetType())
	{
	case CT_RECT:
		return CollisionRectVsPoint(((ColliderRect*)pDest)->GetRectWorld(), m_pos);
		break;
	case  CT_CIRCLE:
		return CollisionCircleVsPoint(((ColliderCircle*)pDest)->GetCircleWorld(), m_pos);
		break;
	case CT_PIXEL:
		return CollisionPixelVsPoint(((ColliderPixel*)pDest)->GetPixels(), ((ColliderPixel*)pDest)->GetWidth(), ((ColliderPixel*)pDest)->GetHeight(), m_pos);
		break;
	}

	return false;
}

void ColliderPoint::Render(HDC hDC, float deltaTime)
{
	Collider::Render(hDC, deltaTime);
}

ColliderPoint* ColliderPoint::Clone()
{
	return new ColliderPoint(*this);
}
