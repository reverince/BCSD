#include "InputManager.h"

DEFINE_SINGLE(InputManager);

InputManager::InputManager() :
	m_pCreateKey(nullptr)
{
}

InputManager::~InputManager()
{
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
		if (pushCount == iter->second->keys.size())
		{
			if (!iter->second->isDown && !iter->second->isPressed)
				iter->second->isDown = true;
			else if (iter->second->isDown && !iter->second->isPressed)
			{
				iter->second->isPressed = true;
				iter->second->isDown = false;
			}
		}
		else
		{
			if (iter->second->isDown || iter->second->isPressed)
			{
				iter->second->isDown = false;
				iter->second->isPressed = false;
				iter->second->isUp = true;
			}
			else if (iter->second->isUp)
				iter->second->isUp = false;
		}
	}
}
