#pragma once
#include "Game.h"

class Core
{
	static Core * m_pInst;
	static bool m_isLooping;

	HINSTANCE m_hInst;
	HWND m_hWnd;
	Resolution m_rs;

	Core();
	~Core();

	ATOM MyRegisterClass();
	BOOL Create();

public:

	static Core * GetInst()
	{
		if (!m_pInst)
			m_pInst = new Core;
		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

	bool Init(HINSTANCE hInst);
	int Run();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
