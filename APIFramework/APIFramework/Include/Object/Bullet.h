#pragma once
#include "DynamicObject.h"

class Bullet : public DynamicObject
{
	friend class Scene;
	friend class Object;

	float m_dist;
	float m_distMax;

	Bullet();
	Bullet(const Bullet & bullet);
	~Bullet();

public:

	void SetDistMax(float distMax) { m_distMax = distMax; }

	virtual Bullet * Clone();
	virtual bool Init();
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual void Collision(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};
