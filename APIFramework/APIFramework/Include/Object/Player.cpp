#include "Player.h"
#include "..\Core.h"

Player::Player() :
	m_fireTime(0.f), m_firePeriod(0.1f)
{
}

Player::Player(const Player & player) :
	DynamicObject(player)
{
	m_fireTime = player.m_fireTime;
	m_firePeriod = player.m_firePeriod;
}

Player::~Player()
{
}

void Player::Fire()
{
	if (m_fireTime <= m_firePeriod)
		return;

	m_fireTime = 0.f;

	Object * pBullet = Object::CloneObject("Bullet", "PlayerBullet", m_pLayer);
	
	pBullet->SetPos(m_pos.x + m_size.x, m_pos.y + (m_size.y - pBullet->GetSize().y) / 2.f);

	SAFE_RELEASE(pBullet);
}

Player * Player::Clone()
{
	return new Player(*this);
}

bool Player::Init()
{
	SetPos(100.f, 100.f);
	SetSize(PLAYER_WIDTH, PLAYER_HEIGHT);
	SetSpeed(PLAYER_SPEED);
	return true;
}

void Player::Input(float deltaTime)
{
	DynamicObject::Input(deltaTime);

	if (GetAsyncKeyState('W') & 0x8000)
	{
		MoveY(deltaTime, MD_BACK);
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		MoveY(deltaTime, MD_FRONT);
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		MoveX(deltaTime, MD_BACK);
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		MoveX(deltaTime, MD_FRONT);
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		Fire();
	}
}

int Player::Update(float deltaTime)
{
	DynamicObject::Update(deltaTime);

	// 이동 관련
	if (m_pos.x + m_size.x >= GET_RESOLUTION.w)
	{
		m_pos.x = GET_RESOLUTION.w - m_size.x;
	}
	else if (m_pos.x <= 0)
	{
		m_pos.x = 0;
	}

	if (m_pos.y + m_size.y >= GET_RESOLUTION.h)
	{
		m_pos.y = GET_RESOLUTION.h - m_size.y;
	}
	else if (m_pos.y <= 0)
	{
		m_pos.y = 0;
	}

	// 발사 관련
	m_fireTime += deltaTime;

	return 0;
}

int Player::LateUpdate(float deltaTime)
{
	DynamicObject::LateUpdate(deltaTime);

	return 0;
}

void Player::Collision(float deltaTime)
{
	DynamicObject::Collision(deltaTime);
}

void Player::Render(HDC hDC, float deltaTime)
{
	DynamicObject::Render(hDC, deltaTime);

	Rectangle(hDC, (int)m_pos.x, (int)m_pos.y, (int)(m_pos.x + m_size.x), (int)(m_pos.y + m_size.y));
}
