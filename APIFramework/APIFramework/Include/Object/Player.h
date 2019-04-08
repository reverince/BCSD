#pragma once
#include "DynamicObject.h"

class Player : public DynamicObject
{
	friend class Object;

	float m_fireTime;
	float m_firePeriod;
	int m_hp;

	Player();
	Player(const Player & player);
	~Player();

	void Fire();

public:

	void Hit(float deltaTime, class Collider * pSrc, class Collider * pDest);
	void HitStay(float deltaTime, class Collider * pSrc, class Collider * pDest);

	virtual bool Init();
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual void Collision(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	virtual Player * Clone();
};
