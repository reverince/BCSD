#include "UIPanel.h"

UIPanel::UIPanel()
{
}

UIPanel::~UIPanel()
{
}

bool UIPanel::Init()
{
	SetPivot(0.f, 0.f);

	return true;
}

void UIPanel::Input(float deltaTime)
{
	UI::Input(deltaTime);
}

int UIPanel::Update(float deltaTime)
{
	UI::Update(deltaTime);

	return 0;
}

int UIPanel::LateUpdate(float deltaTime)
{
	UI::LateUpdate(deltaTime);

	return 0;
}

void UIPanel::Collision(float deltaTime)
{
	UI::Collision(deltaTime);
}

void UIPanel::Render(HDC hDC, float deltaTime)
{
	UI::Render(hDC, deltaTime);
}

UIPanel* UIPanel::Clone()
{
	return new UIPanel(*this);
}
