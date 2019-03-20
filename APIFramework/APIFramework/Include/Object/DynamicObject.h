#pragma once
#include "Object.h"

class DynamicObject : public Object
{
protected:

	DynamicObject();
	DynamicObject(const DynamicObject  & obj);
	virtual ~DynamicObject() = 0;

	virtual bool Init() = 0;
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual void Collision(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};
