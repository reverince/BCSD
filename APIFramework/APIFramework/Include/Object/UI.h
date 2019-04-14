#pragma once
#include "Object.h"

class UI : public Object
{
protected:

	UI();
	UI(const UI& ui) : Object(ui) { }
	virtual ~UI() = 0;

public:

	virtual bool Init() = 0;
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual void Collision(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	virtual UI * Clone() = 0;
};
