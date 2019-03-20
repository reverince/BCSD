#pragma once
#include "Object.h"

class DynamicObject : public Object
{
	float m_angle;
	float m_speed;

protected:

	DynamicObject();
	DynamicObject(const DynamicObject  & obj);
	virtual ~DynamicObject() = 0;

	void Move(float x, float y);
	void Move(float x, float y, float deltaTime);
	void Move(const POSITION & move);
	void Move(const POSITION & move, float deltaTime);
	void MoveX(float deltaTime, MOVE_DIR dir);
	void MoveY(float deltaTime, MOVE_DIR dir);
	void MoveAngle(float speed);
	void MoveAngle(float speed, float deltaTime);

	virtual bool Init() = 0;
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual void Collision(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);

public:

	void SetAngle(float angle) { m_angle = angle; }
	void SetSpeed(float speed) { m_speed = speed; }
	float GetAngle() const { return m_angle; }
	float GetSpeed() const { return m_speed; }
};
