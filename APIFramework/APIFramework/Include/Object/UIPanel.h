#pragma once
#include "UI.h"

class UIPanel : public UI
{
	friend class Object;
	friend class Scene;

	UIPanel();
	UIPanel(const UIPanel& ui) : UI(ui) { }
	~UIPanel();

	virtual bool Init();
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual void Collision(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	virtual UIPanel* Clone();
};
