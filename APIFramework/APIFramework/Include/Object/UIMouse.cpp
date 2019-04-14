#include "UIMouse.h"
#include "..\Core\Core.h"
#include "..\Collider\ColliderPoint.h"

UIMouse::UIMouse()
{
}

UIMouse::UIMouse(const UIMouse& ui) :
	UI(ui)
{
}

UIMouse::~UIMouse()
{
}

void UIMouse::Hit(float deltaTime, Collider* pSrc, Collider* pDest)
{
}

bool UIMouse::Init()
{
	POINT pos;
	// 스크린 좌표
	GetCursorPos(&pos);
	// 클라이언트 좌표
	ScreenToClient(GET_WINDOWHANDLE, &pos);

	m_pos = pos;

	//ShowCursor(FALSE);

	ColliderPoint* pColl = AddCollider<ColliderPoint>("Cursor");

	SAFE_RELEASE(pColl);

	return true;
}

void UIMouse::Input(float deltaTime)
{
	UI::Input(deltaTime);
}

int UIMouse::Update(float deltaTime)
{
	UI::Update(deltaTime);

	POINT pos;
	// 스크린 좌표
	GetCursorPos(&pos);
	// 클라이언트 좌표
	ScreenToClient(GET_WINDOWHANDLE, &pos);

	m_move.x = pos.x - m_pos.x;
	m_move.y = pos.y - m_pos.y;

	m_pos = pos;

	return 0;
}

int UIMouse::LateUpdate(float deltaTime)
{
	UI::LateUpdate(deltaTime);

	return 0;
}

void UIMouse::Collision(float deltaTime)
{
	UI::Collision(deltaTime);
}

void UIMouse::Render(HDC hDC, float deltaTime)
{
	UI::Render(hDC, deltaTime);
}

UIMouse* UIMouse::Clone()
{
	return new UIMouse(*this);
}
