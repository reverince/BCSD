#include "InputManager.h"
#include "..\Scene\Layer.h"
#include "..\Object\UIMouse.h"
#include "..\Collider\CollisionManager.h"
#include "..\Animation\Animation.h"

DEFINE_SINGLE(InputManager);

InputManager::InputManager() :
	m_pCreateKey(nullptr), m_pMouse(nullptr)
{
}

InputManager::~InputManager()
{
	Object::EraseObject(m_pMouse);
	SAFE_RELEASE(m_pMouse);
	SafeDeleteMap(m_mapKey);
}

KEYINFO * InputManager::FindKey(const string & key) const
{
	unordered_map<string, KEYINFO *>::const_iterator iter = m_mapKey.find(key);

	if (iter == m_mapKey.end())
		return nullptr;

	return iter->second;
}

bool InputManager::KeyDown(const string & key) const
{
	KEYINFO * pInfo = FindKey(key);

	if (!pInfo)
		return false;

	return pInfo->isDown;
}

bool InputManager::KeyPress(const string & key) const
{
	KEYINFO * pInfo = FindKey(key);

	if (!pInfo)
		return false;

	return pInfo->isPressed;
}

bool InputManager::KeyUp(const string & key) const
{
	KEYINFO * pInfo = FindKey(key);

	if (!pInfo)
		return false;

	return pInfo->isUp;
}

bool InputManager::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	AddKey('W', "MoveUp");
	AddKey('S', "MoveDown");
	AddKey('A', "MoveLeft");
	AddKey('D', "MoveRight");
	AddKey(VK_SPACE, "Fire");
	AddKey(VK_SHIFT, "Slow");
	AddKey(VK_LBUTTON, "LeftClick");
	
	GetCursorPos(&m_cursorPos);
	m_pMouse = Object::CreateObject<UIMouse>("Cursor");
	m_pMouse->SetSize(CURSOR_WIDTH, CURSOR_HEIGHT);
	m_pMouse->SetTexture("Cursor", CURSOR_TEXTURE);

	// 애니메이션
	//Animation* pAnim = m_pMouse->CreateAnimation("CursorAnim");
	//
	//SAFE_RELEASE(pAnim);

	return true;
}

void InputManager::Update(float deltaTime)
{
	unordered_map<string, KEYINFO *>::iterator iter;

	for (iter = m_mapKey.begin(); iter != m_mapKey.end(); ++iter)
	{
		int pushCount = 0;

		for (size_t i = 0; i < iter->second->keys.size(); ++i)
		{
			if (GetAsyncKeyState(iter->second->keys[i]) & 0x8000)
				++pushCount;
		}

		// 입력 상태 변경 (down press up)
		if (pushCount == iter->second->keys.size())  // Press
		{
			if (!iter->second->isDown && !iter->second->isPressed)
			{
				iter->second->isDown = true;
				iter->second->isPressed = true;
				iter->second->isUp = false;
			}
			else if (iter->second->isDown)
				iter->second->isDown = false;
		}
		else  // Up
		{
			if (iter->second->isPressed)
			{
				iter->second->isDown = false;
				iter->second->isPressed = false;
				iter->second->isUp = true;
			}
			else if (iter->second->isUp)
				iter->second->isUp = false;
		}
	}

	m_pMouse->Update(deltaTime);
	m_pMouse->LateUpdate(deltaTime);

	GET_SINGLE(CollisionManager)->AddObject(m_pMouse);
}
