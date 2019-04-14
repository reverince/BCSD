#include "UIButton.h"
#include "..\Collider\ColliderRect.h"

UIButton::UIButton() :
	m_isCallbackEnabled(false)
{
}

UIButton::UIButton(const UIButton& ui) :
	UI(ui)
{
	m_isCallbackEnabled = false;
}

UIButton::~UIButton()
{
}

void UIButton::MouseOn(float deltaTime, Collider* pSrc, Collider* pDest)
{
}

void UIButton::MouseOff(float deltaTime, Collider* pSrc, Collider* pDest)
{
}

bool UIButton::Init()
{
	ColliderRect* pColl = AddCollider<ColliderRect>("ButtonBody");

	SAFE_RELEASE(pColl);

	return true;
}

void UIButton::Input(float deltaTime)
{
	UI::Input(deltaTime);
}

int UIButton::Update(float deltaTime)
{
	UI::Update(deltaTime);

	return 0;
}

int UIButton::LateUpdate(float deltaTime)
{
	UI::LateUpdate(deltaTime);

	return 0;
}

void UIButton::Collision(float deltaTime)
{
	UI::Collision(deltaTime);
}

void UIButton::Render(HDC hDC, float deltaTime)
{
	UI::Render(hDC, deltaTime);
}

UIButton* UIButton::Clone()
{
	return new UIButton(*this);
}
