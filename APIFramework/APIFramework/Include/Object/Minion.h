#pragma once
#include "DynamicObject.h"

class Minion : public DynamicObject
{
	friend class Object;

	MOVE_DIR m_dir;
	float m_fireTime;
	float m_firePeriod;

	Minion();
	Minion(const Minion & minion);
	~Minion();

	void Fire();

public:

	virtual Minion * Clone();
	virtual bool Init();
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual void Collision(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};
