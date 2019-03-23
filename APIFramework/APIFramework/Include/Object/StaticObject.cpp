#include "StaticObject.h"

StaticObject::StaticObject()
{
}

StaticObject::StaticObject(const StaticObject & obj) :
	Object(obj)
{
}

StaticObject::~StaticObject()
{
}

void StaticObject::Input(float deltaTime)
{
	Object::Input(deltaTime);
}

int StaticObject::Update(float deltaTime)
{
	Object::Update(deltaTime);

	return 0;
}

int StaticObject::LateUpdate(float deltaTime)
{
	Object::LateUpdate(deltaTime);

	return 0;
}

void StaticObject::Collision(float deltaTime)
{
	Object::Collision(deltaTime);
}

void StaticObject::Render(HDC hDC, float deltaTime)
{
	Object::Render(hDC, deltaTime);
}
