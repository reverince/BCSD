#pragma once
#include "..\Game.h"

class Core
{
	static Core * m_pInst;
	static bool m_isLooping;

	HINSTANCE m_hInst;
	HWND m_hWnd;
	HDC m_hDC;
	RESOLUTION m_rs;

	Core();
	~Core();

	ATOM MyRegisterClass();
	BOOL Create();

	void Logic();
	void Input(float deltaTime);
	int Update(float deltaTime);
	int LateUpdate(float deltaTime);
	void Collision(float deltaTime);
	void Render(float deltaTime);

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

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	RESOLUTION GetResolution() const { return m_rs; }

	bool Init(HINSTANCE hInst);
	int Run();
};
