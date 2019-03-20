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
}

int StaticObject::Update(float deltaTime)
{
	return 0;
}

int StaticObject::LateUpdate(float deltaTime)
{
	return 0;
}

void StaticObject::Collision(float deltaTime)
{
}

void StaticObject::Render(HDC hDC, float deltaTime)
{
}
