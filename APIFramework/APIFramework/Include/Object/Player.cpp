#include "Player.h"

Player::Player()
{
}

Player::Player(const Player & player) :
	DynamicObject(player)
{
}

Player::~Player()
{
}

bool Player::Init()
{
	SetPos(100.f, 100.f);
	SetSize(100.f, 100.f);
	SetSpeed(500.f);
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
}

int Player::Update(float deltaTime)
{
	DynamicObject::Update(deltaTime);
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
