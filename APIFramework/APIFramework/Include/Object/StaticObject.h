#pragma once
#include "Object.h"

class StaticObject : public Object
{
protected:

	StaticObject();
	StaticObject(const StaticObject  & obj);
	virtual ~StaticObject() = 0;

	virtual bool Init() = 0;
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual void Collision(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};
