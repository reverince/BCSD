#include "DynamicObject.h"

DynamicObject::DynamicObject() :
	m_angle(0.f), m_speed(100.f)
{
}

DynamicObject::DynamicObject(const DynamicObject & obj) :
	Object(obj)
{
}

DynamicObject::~DynamicObject()
{
}

void DynamicObject::Move(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void DynamicObject::Move(float x, float y, float deltaTime)
{
	m_pos.x = x * deltaTime;
	m_pos.y = y * deltaTime;
}

void DynamicObject::Move(const POSITION & move)
{
	m_pos += move;
}

void DynamicObject::Move(const POSITION & move, float deltaTime)
{
	m_pos += move * deltaTime;
}

void DynamicObject::MoveX(float x)
{
	m_pos.x += x;
}

void DynamicObject::MoveX(float x, float deltaTime)
{
	m_pos.x += x * deltaTime;
}

void DynamicObject::MoveY(float y)
{
	m_pos.y += y;
}

void DynamicObject::MoveY(float y, float deltaTime)
{
	m_pos.y += y * deltaTime;
}

void DynamicObject::MoveX(float deltaTime, MOVE_DIR dir)
{
	m_pos.x += m_speed * deltaTime * dir;
}

void DynamicObject::MoveY(float deltaTime, MOVE_DIR dir)
{
	m_pos.y += m_speed * deltaTime * dir;
}

void DynamicObject::MoveAngle(float speed)
{
	m_pos.x += cosf(m_angle) * speed;
	m_pos.y += sinf(m_angle) * speed;
}

void DynamicObject::MoveAngle(float speed, float deltaTime)
{
	m_pos.x += cosf(m_angle) * speed * deltaTime;
	m_pos.y += sinf(m_angle) * speed * deltaTime;
}

void DynamicObject::Input(float deltaTime)
{
	Object::Input(deltaTime);
}

int DynamicObject::Update(float deltaTime)
{
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
}
