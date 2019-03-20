#pragma once
#include "DynamicObject.h"

class Player : public DynamicObject
{
	friend class Object;

	Player();
	Player(const Player & player);
	~Player();

public:

	virtual bool Init();
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual void Collision(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};
