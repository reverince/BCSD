#include "DynamicObject.h"

DynamicObject::DynamicObject()
{
}

DynamicObject::DynamicObject(const DynamicObject & obj) :
	Object(obj)
{
}

DynamicObject::~DynamicObject()
{
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
