#pragma once
#include "UI.h"

class UIMouse : public UI
{
	friend class Object;
	friend class Scene;

	POINT m_pos;
	POINT m_move;

	UIMouse();
	UIMouse(const UIMouse& ui);
	~UIMouse();

public:

	void Hit(float deltaTime, class Collider* pSrc, class Collider* pDest);

	virtual bool Init();
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual void Collision(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	virtual UIMouse* Clone();
};
