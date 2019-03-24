#include "Collider.h"
#include "..\Object\Object.h"

Collider::Collider()
{
}

Collider::Collider(const Collider & collider)
{
	*this = collider;
}

Collider::~Collider()
{
	for (list<Collider *>::iterator iter = m_listCollision.begin(); iter != m_listCollision.end(); ++iter)
		(*iter)->EraseCollision(this);
}

bool Collider::CollisionRectVsRect(const RECTANGLE & src, const RECTANGLE & dest)
{
	if (src.l > dest.r || src.r < dest.l || src.t > dest.b || src.b < dest.t)
		return false;

	return true;
}

bool Collider::Init()
{
	return false;
}

void Collider::Input(float deltaTime)
{
}

int Collider::Update(float deltaTime)
{
	return 0;
}

int Collider::LateUpdate(float deltaTime)
{
	return 0;
}

bool Collider::Collision(Collider * pDest)
{
	return false;
}

void Collider::Render(HDC hDC, float deltaTime)
{
}

Collider * Collider::Clone()
{
	return nullptr;
}
