#include "Minion.h"
#include "..\Core\Core.h"

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
	SetSize(MINION_WIDTH, MINION_HEIGHT);
	SetSpeed(MINION_SPEED);

	return true;
}

int Minion::Update(float deltaTime)
{
	DynamicObject::Update(deltaTime);

	// 이동 관련
	MoveY(deltaTime, m_dir);

	if (m_pos.y >= GET_RESOLUTION.h)
	{
		m_pos.y = GET_RESOLUTION.h;
		m_dir = MD_BACK;
	}
	else if (m_pos.y <= 0)
	{
		m_pos.y = 0;
		m_dir = MD_FRONT;
	}

	// 발사 관련
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

	POSITION pos = m_pos - m_size * m_pivot;
	Rectangle(hDC, (int)pos.x, (int)pos.y, (int)(pos.x + m_size.x), (int)(pos.y + m_size.y));
}
