#include "Bullet.h"

Bullet::Bullet() :
	m_dist(0.f), m_distMax(1000.f)
{
}

Bullet::Bullet(const Bullet & bullet) :
	DynamicObject(bullet)
{
	m_dist = bullet.m_dist;
	m_distMax = bullet.m_distMax;
}

Bullet::~Bullet()
{
}

Bullet * Bullet::Clone()
{
	return new Bullet(*this);
}

bool Bullet::Init()
{
	SetSize(20.f, 20.f);
	SetSpeed(1000.f);

	return true;
}

int Bullet::Update(float deltaTime)
{
	DynamicObject::Update(deltaTime);

	MoveAngle(deltaTime);

	m_dist += GetSpeed() * deltaTime;

	if (m_dist > m_distMax)
		Die();

	return 0;
}

int Bullet::LateUpdate(float deltaTime)
{
	DynamicObject::LateUpdate(deltaTime);

	return 0;
}

void Bullet::Collision(float deltaTime)
{
	DynamicObject::Collision(deltaTime);
}

void Bullet::Render(HDC hDC, float deltaTime)
{
	DynamicObject::Render(hDC, deltaTime);

	Ellipse(hDC, (int)m_pos.x, (int)m_pos.y, (int)(m_pos.x + m_size.x), (int)(m_pos.y + m_size.y));
}
