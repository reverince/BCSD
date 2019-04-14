#include "ColliderPixel.h"
#include "..\Core\PathManager.h"
#include "..\Object\Object.h"
#include "ColliderCircle.h"
#include "ColliderRect.h"
#include "ColliderPoint.h"

ColliderPixel::ColliderPixel() :
	m_width(0), m_height(0)
{
	m_type = CT_PIXEL;
}

ColliderPixel::ColliderPixel(const ColliderPixel& collider) :
	Collider(collider)
{
	m_width = collider.m_width;
	m_height = collider.m_height;
}

ColliderPixel::~ColliderPixel()
{
}

bool ColliderPixel::Init()
{
	return true;
}

void ColliderPixel::Input(float deltaTime)
{
}

int ColliderPixel::Update(float deltaTime)
{
	return 0;
}

int ColliderPixel::LateUpdate(float deltaTime)
{
	return 0;
}

bool ColliderPixel::Collision(Collider* pDest)
{
	switch (pDest->GetType())
	{
	case CT_RECT:
		return CollisionRectVsPixel(((ColliderRect*)pDest)->GetRectWorld(), m_pixels, m_width, m_height);
		break;
	case CT_POINT:
		return CollisionPixelVsPoint(m_pixels, m_width, m_height, ((ColliderPoint*)pDest)->GetPos());
		break;
	}

	return false;
}

void ColliderPixel::Render(HDC hDC, float deltaTime)
{
}

ColliderPixel* ColliderPixel::Clone()
{
	return new ColliderPixel(*this);
}
