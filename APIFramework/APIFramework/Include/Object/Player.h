#pragma once
#include "DynamicObject.h"

class Player : public DynamicObject
{
private:

	Player();
	Player(const Player & player);
	~Player();

public:

	bool Init() = 0;
	void Input(float deltaTime);
	int Update(float deltaTime);
	int LateUpdate(float deltaTime);
	void Collision(float deltaTime);
	void Render(HDC hDC, float deltaTime);
};
