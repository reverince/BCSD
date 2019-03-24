#pragma once
#include "..\Game.h"

class Core
{
	DECLARE_SINGLE(Core)

	static bool m_isLooping;

	HINSTANCE m_hInst;
	HWND m_hWnd;
	HDC m_hDC;
	RESOLUTION m_rs;

	ATOM MyRegisterClass();
	BOOL Create();

	void Logic();
	void Input(float deltaTime);
	int Update(float deltaTime);
	int LateUpdate(float deltaTime);
	void Collision(float deltaTime);
	void Render(float deltaTime);

public:

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	RESOLUTION GetResolution() const { return m_rs; }

	bool Init(HINSTANCE hInst);
	int Run();
};
