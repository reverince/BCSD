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
}

int DynamicObject::Update(float deltaTime)
{
	return 0;
}

int DynamicObject::LateUpdate(float deltaTime)
{
	return 0;
}

void DynamicObject::Collision(float deltaTime)
{
}

void DynamicObject::Render(HDC hDC, float deltaTime)
{
}
