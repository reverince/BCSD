#include "Minion.h"
#include "..\Core\Core.h"
#include "..\Collider\ColliderRect.h"
#include "Bullet.h"

Minion::Minion() :
	m_dir(MD_FRONT), m_fireTime(0.f), m_firePeriod(0.5f)
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
	if (Object * pPlayer = Object::FindObject("Player"))
	{
		Object * pBullet = Object::CloneObject("Bullet", "MinionBullet", m_pLayer);

		pBullet->AddCollisionFunc("Bullet", CS_ENTER, (Bullet *)pBullet, &Bullet::Hit);

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

		// ���� ����� �ʱ����� ó�������� �Ƚ��϶�
		theta = (dx == 0.f) ? (dy > 0.f) ? 1.5f * PI : 0.5f * PI : (atanf(dy / dx) + ((dx > 0.f) ? PI : (dy < 0.f && dx < 0.f) ? 2.f * PI : 0.f));

		pBullet->SetPos(m_pos);
		((DynamicObject *)pBullet)->SetAngle(theta);
		((DynamicObject *)pBullet)->SetSpeed(BULLET_SPEED * 0.5f);

		SAFE_RELEASE(pBullet);
	}
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

	ColliderRect * pCollRect = AddCollider<ColliderRect>("Minion");
	pCollRect->SetRect(-MINION_WIDTH * 0.4f, -MINION_HEIGHT * 0.4f, MINION_WIDTH * 0.4f, MINION_HEIGHT * 0.4f);

	SAFE_RELEASE(pCollRect);

	return true;
}

int Minion::Update(float deltaTime)
{
	DynamicObject::Update(deltaTime);

	// �̵� ����
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

	// �߻� ����
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
