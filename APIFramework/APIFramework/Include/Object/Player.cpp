#include "Player.h"
#include "..\Core\Core.h"

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
	
	POSITION pos;
	pos.x = m_pos.x + m_size.x * (1.f - m_pivot.x);
	pos.y = m_pos.y + m_size.y * (0.5f - m_pivot.y);

	pBullet->SetPos(pos.x, pos.y);

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
	SetTexture("Player", PLAYER_TEXTURE_NORMAL);

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
	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
		SetSpeed(PLAYER_SPEED_SLOW);
	else
		SetSpeed(PLAYER_SPEED);

}

int Player::Update(float deltaTime)
{
	DynamicObject::Update(deltaTime);

	// 이동 관련
	if (m_pos.x >= GET_RESOLUTION.w)
	{
		m_pos.x = (float)GET_RESOLUTION.w;
	}
	else if (m_pos.x <= 0)
	{
		m_pos.x = 0;
	}

	if (m_pos.y >= GET_RESOLUTION.h)
	{
		m_pos.y = (float)GET_RESOLUTION.h;
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
}
