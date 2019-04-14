#include "ColliderRect.h"
#include "..\Object\Object.h"
#include "ColliderCircle.h"
#include "ColliderPixel.h"

ColliderRect::ColliderRect()
{
	m_type = CT_RECT;
}

ColliderRect::ColliderRect(const ColliderRect & collider) :
	Collider(collider)
{
	m_rect = collider.m_rect;
}

ColliderRect::~ColliderRect()
{
}

bool ColliderRect::Init()
{
	return true;
}

void ColliderRect::Input(float deltaTime)
{
	Collider::Input(deltaTime);
}

int ColliderRect::Update(float deltaTime)
{
	Collider::Update(deltaTime);

	return 0;
}

int ColliderRect::LateUpdate(float deltaTime)
{
	Collider::LateUpdate(deltaTime);
	//POSITION pos = m_pos - m_size * m_pivot;
	POSITION pos = m_pObj->GetPos() - m_pObj->GetSize() * m_pObj->GetPivot();
	m_rectWorld.l = pos.x + m_rect.l;
	m_rectWorld.t = pos.y + m_rect.t;
	m_rectWorld.r = pos.x + m_rect.r;
	m_rectWorld.b = pos.y + m_rect.b;
	
	return 0;
}

bool ColliderRect::Collision(Collider * pDest)
{
	switch (pDest->GetType())
	{
	case CT_RECT:
		return CollisionRectVsRect(m_rectWorld, ((ColliderRect *)pDest)->GetRectWorld());
		break;
	case  CT_CIRCLE:
		return CollisionRectVsCircle(m_rectWorld, ((ColliderCircle *)pDest)->GetCircleWorld());
		break;
	case CT_PIXEL:
		return CollisionRectVsPixel(m_rectWorld, ((ColliderPixel *)pDest)->GetPixels(), ((ColliderPixel *)pDest)->GetWidth(), ((ColliderPixel *)pDest)->GetHeight());
		break;
	}

	return false;
}

void ColliderRect::Render(HDC hDC, float deltaTime)
{
	Collider::Render(hDC, deltaTime);

#ifdef _DEBUG
	MoveToEx(hDC, (int)m_rectWorld.l, (int)m_rectWorld.t, NULL);
	LineTo(hDC, (int)m_rectWorld.r, (int)m_rectWorld.t);
	LineTo(hDC, (int)m_rectWorld.r, (int)m_rectWorld.b);
	LineTo(hDC, (int)m_rectWorld.l, (int)m_rectWorld.b);
	LineTo(hDC, (int)m_rectWorld.l, (int)m_rectWorld.t);
#endif
}

ColliderRect * ColliderRect::Clone()
{
	return new ColliderRect(*this);
}
