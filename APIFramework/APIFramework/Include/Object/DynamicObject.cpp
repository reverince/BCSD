#include "DynamicObject.h"

DynamicObject::DynamicObject() :
	m_angle(0.f), m_speed(100.f), m_isMoving(false), m_isFalling(false), m_force(0.f), m_forceOrigin(0.f)
{
}

DynamicObject::DynamicObject(const DynamicObject & obj) :
	Object(obj)
{
	m_angle = obj.m_angle;
	m_speed = obj.m_speed;
	m_isMoving = false;
	m_isFalling = false;
	m_force = 0.f;
	m_forceOrigin = obj.m_forceOrigin;
}

DynamicObject::~DynamicObject()
{
}

void DynamicObject::Move(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
	m_isMoving = true;
}
void DynamicObject::Move(float x, float y, float deltaTime)
{
	m_pos.x = x * deltaTime;
	m_pos.y = y * deltaTime;
	m_isMoving = true;
}
void DynamicObject::Move(const POSITION & move)
{
	m_pos += move;
	m_isMoving = true;
}
void DynamicObject::Move(const POSITION & move, float deltaTime)
{
	m_pos += move * deltaTime;
	m_isMoving = true;
}
void DynamicObject::MoveX(float deltaTime, MOVE_DIR dir)
{
	m_pos.x += m_speed * deltaTime * dir;
	m_isMoving = true;
}
void DynamicObject::MoveY(float deltaTime, MOVE_DIR dir)
{
	m_pos.y += m_speed * deltaTime * dir;
	m_isMoving = true;
}
void DynamicObject::MoveAngle()
{
	m_pos.x += cosf(m_angle) * m_speed;
	m_pos.y += sinf(m_angle) * m_speed;
	m_isMoving = true;
}
void DynamicObject::MoveAngle(float deltaTime)
{
	m_pos.x += cosf(m_angle) * m_speed * deltaTime;
	m_pos.y += sinf(m_angle) * m_speed * deltaTime;
	m_isMoving = true;
}

void DynamicObject::Jump()
{
	if (m_isFalling)
		return;
	m_isFalling = true;
	m_force = m_forceOrigin;
}

void DynamicObject::JumpEnd()
{
	if (!m_isFalling)
		return;
	m_isFalling = false;
	m_force = 0.f;
}

void DynamicObject::Input(float deltaTime)
{
	Object::Input(deltaTime);
}

int DynamicObject::Update(float deltaTime)
{
	if (m_hasPhysics)
	{
		m_gravityTime += deltaTime;

		// มกวม
		m_force -= (GRAVITY * m_gravityTime);
		m_pos.y -= m_force * deltaTime;
	}

	Object::Update(deltaTime);

	return 0;
}

int DynamicObject::LateUpdate(float deltaTime)
{
	Object::LateUpdate(deltaTime);

	return 0;
}

void DynamicObject::Collision(float deltaTime)
{
	Object::Collision(deltaTime);
}

void DynamicObject::Render(HDC hDC, float deltaTime)
{
	Object::Render(hDC, deltaTime);

	m_isMoving = false;
}
