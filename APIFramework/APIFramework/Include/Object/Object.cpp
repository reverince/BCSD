#include "Object.h"

Object::Object()
{
}

Object::Object(const Object & obj)
{
	*this = obj;
}

Object::~Object()
{
}

bool Object::Init()
{
	return true;
}

void Object::Input(float deltaTime)
{
}

int Object::Update(float deltaTime)
{
	return 0;
}

int Object::LateUpdate(float deltaTime)
{
	return 0;
}

void Object::Collision(float deltaTime)
{
}

void Object::Render(HDC hDC, float deltaTime)
{
}
