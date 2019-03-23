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
	Object * pPlayer = Object::FindObject("Player");

	float dy = m_pos.y - pPlayer->GetPos().y;
	float dx = m_pos.x - pPlayer->GetPos().x;
	float theta;

	/*if (dx == 0.f)
		theta = (dy > 0.f) ? 1.5f * PI : 0.5f * PI;
	else
	{
		theta = atanf(dy / dx);
		theta += (dx > 0.f) ? PI : (dy < 0.f && dx < 0.f) ? 2.f * PI : 0.f;
	}*/

	// 각도 계산은 너굴맨이 처리했으니 안심하라구
	theta = (dx == 0.f) ? (dy > 0.f) ? 1.5f * PI : 0.5f * PI : (atanf(dy / dx) + ( (dx > 0.f) ? PI : (dy < 0.f && dx < 0.f) ? 2.f * PI : 0.f ));

	((DynamicObject *)pBullet)->SetAngle(theta);
	pBullet->SetPos(m_pos);
	((DynamicObject *)pBullet)->SetSpeed(BULLET_SPEED * 0.5f);

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
	SetTexture("Minion", MINION_TEXTURE);

	return true;
}

int Minion::Update(float deltaTime)
{
	DynamicObject::Update(deltaTime);

	// 이동 관련
	MoveY(deltaTime, m_dir);

	if (m_pos.y >= GET_RESOLUTION.h)
	{
		m_pos.y = (float)GET_RESOLUTION.h;
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
}
