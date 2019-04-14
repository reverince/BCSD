#pragma once
#include "UI.h"

class UIButton : public UI
{
	friend class Object;
	friend class Scene;

	UIButton();
	UIButton(const UIButton& ui) : UI(ui) { }
	~UIButton();

public:

	virtual bool Init();
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual void Collision(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	virtual UIButton* Clone();
};
