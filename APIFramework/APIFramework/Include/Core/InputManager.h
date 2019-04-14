#pragma once
#include "..\Game.h"

typedef struct KeyInfo
{
	string name;
	vector<DWORD> keys;
	bool isDown;
	bool isPressed;
	bool isUp;

	KeyInfo() : isDown(false), isPressed(false), isUp(false) { }
} KEYINFO;

class InputManager
{
	DECLARE_SINGLE(InputManager);

	HWND m_hWnd;
	unordered_map<string, KEYINFO *> m_mapKey;
	KEYINFO * m_pCreateKey;

	POINT m_cursorPos;
	POINT m_cursorMove;
	class UIMouse* m_pMouse;

public:

	class UIMouse* GetMouse() const { return m_pMouse; }

	template <typename T>
	bool AddKey(const T & data)
	{
		if (!m_pCreateKey)
			m_pCreateKey = new KEYINFO;

		const char * pTType = typeid(T).name();

		if (strcmp(pTType, "char") == 0 || strcmp(pTType, "int") == 0)
		{
			m_pCreateKey->keys.push_back((DWORD)data);
		}
		else
		{
			m_pCreateKey->name = data;
			m_mapKey.insert(make_pair(m_pCreateKey->name, m_pCreateKey));
		}

		return true;
	}

	template <typename T, typename ... Ts>
	bool AddKey(const T & data, const Ts & ... args)
	{
		if (!m_pCreateKey)
			m_pCreateKey = new KEYINFO;

		const char * pTType = typeid(T).name();

		if (strcmp(pTType, "char") == 0 || strcmp(pTType, "int") == 0)
		{
			m_pCreateKey->keys.push_back(data);
		}
		else
		{
			m_pCreateKey->name = data;
			m_mapKey.insert(make_pair(m_pCreateKey->name, m_pCreateKey));
		}

		AddKey(args ...);

		if (m_pCreateKey)
			m_pCreateKey = nullptr;

		return true;
	}

	KEYINFO * FindKey(const string & key) const;

	bool KeyDown(const string & key) const;
	bool KeyPress(const string & key) const;
	bool KeyUp(const string & key) const;

	bool Init(HWND hWnd);
	void Update(float deltaTime);
};
