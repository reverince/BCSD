#include "Minion.h"
#include "..\Core.h"

Minion::Minion() :
	m_dir(MD_FRONT), m_fireTime(0.f), m_firePeriod(2.f)
{
}

Minion::Minion(const Minion & minion) :
	DynamicObject(minion)
{
	m_dir = minion.m_dir;
	m_fireTime = minion.m_fireTime;
	m_firePeriod = minion.m_firePeriod;
}

Minion::~Minion()
{
}

void Minion::Fire()
{
	Object * pBullet = Object::CloneObject("Bullet", "MinionBullet", m_pLayer);

	// 왼쪽으로 발사
	((DynamicObject *)pBullet)->SetAngle(PI);

	pBullet->SetPos(m_pos.x - pBullet->GetSize().x, m_pos.y + (m_size.y - pBullet->GetSize().y) / 2.f);

	SAFE_RELEASE(pBullet);
}

Minion * Minion::Clone()
{
	return new Minion(*this);
}

bool Minion::Init()
{
	SetPos(1400.f, 100.f);
	SetSize(50.f, 50.f);
	SetSpeed(200.f);

	return true;
}

int Minion::Update(float deltaTime)
{
	DynamicObject::Update(deltaTime);

	// 이동
	MoveY(deltaTime, m_dir);

	if (m_pos.y + m_size.y >= GET_RESOLUTION.h)
	{
		m_pos.y = GET_RESOLUTION.h - m_size.y;
		m_dir = MD_BACK;
	}
	else if (m_pos.y <= 0)
	{
		m_pos.y = 0;
		m_dir = MD_FRONT;
	}

	// 장전 발사
	m_fireTime += deltaTime;

	if (m_fireTime > m_firePeriod)
	{
		m_fireTime -= m_firePeriod;
		Fire();
	}

	return 0;
}

int Minion::LateUpdate(float deltaTime)
{
	DynamicObject::LateUpdate(deltaTime);

	return 0;
}

void Minion::Collision(float deltaTime)
{
	DynamicObject::Collision(deltaTime);
}

void Minion::Render(HDC hDC, float deltaTime)
{
	DynamicObject::Render(hDC, deltaTime);

	Rectangle(hDC, (int)m_pos.x, (int)m_pos.y, (int)(m_pos.x + m_size.x), (int)(m_pos.y + m_size.y));
}
