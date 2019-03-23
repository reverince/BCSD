#pragma once
#include "StaticObject.h"

class Stage : public StaticObject
{
	friend class Scene;
	friend class Object;
	Stage();
	Stage(const Stage & stage);
	~Stage();

public:

	virtual Stage * Clone();
	virtual bool Init();
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual void Collision(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};
