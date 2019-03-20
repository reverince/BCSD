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
	return true;
}

void Player::Input(float deltaTime)
{
}

int Player::Update(float deltaTime)
{
	return 0;
}

int Player::LateUpdate(float deltaTime)
{
	return 0;
}

void Player::Collision(float deltaTime)
{
}

void Player::Render(HDC hDC, float deltaTime)
{
	Rectangle(hDC, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y);
}
