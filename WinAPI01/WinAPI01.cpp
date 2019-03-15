// WinAPI01.cpp : 응용 프로그램 진입점 정의
//

#include "stdafx.h"
#include "WinAPI01.h"
#include <list>
#define _USE_MATH_DEFINES  // for M_PI
#include <math.h>
using namespace std;

#define MAX_LOADSTRING 100
#define WND_WIDTH 800.f
#define WND_HEIGHT 600.f
#define PLAYER_RADIUS 30.f
#define PLAYER_SPEED 500.f
#define GUN_LENGTH 50.f
#define BULLET_RADIUS 10.f
#define BULLET_SPEED 1000.f
#define MONSTER_RADIUS 50.f
#define MONSTER_SPEED 500.f

enum MV_DIR { MV_UP = -1, MV_DOWN = 1 };

struct AreaSelection  // 마우스 드래그 영역 표시
{
	bool isStarted;
	POINT start;
	POINT end;
};

struct FloatRectangle
{
	float left, top, right, bottom;
};

struct FloatCircle
{
	float x, y, r;
};

struct Bullet
{
	FloatCircle circle;
	float angle;
	float dist;
	float distLimit;  // 사거리
};

struct Monster
{
	FloatCircle circle;
	float speed;
	int dir;
	float time;
	float timeLimit;
};

// 전역 변수

HINSTANCE hInst;  // 현재 인스턴스
WCHAR szTitle[MAX_LOADSTRING];  // 제목 표시줄 텍스트
WCHAR szWindowClass[MAX_LOADSTRING];  // 기본 창 클래스 이름

AreaSelection g_areaSelection;
HWND g_hWnd;
HDC g_hDC;
bool g_isLooping = true;  // 메시지 확인

FloatCircle g_playerCircle = { 50.f, 50.f, PLAYER_RADIUS };
float g_playerAngle;
POINT g_gunPos;
float g_gunLength = GUN_LENGTH;
Monster g_monster;

list<Bullet> g_playerBulletList;
list<Bullet> g_monsterBulletList;

LARGE_INTEGER g_second;
LARGE_INTEGER g_time;
float g_deltaTime;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void Run()
{
	// deltaTime
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	g_deltaTime = (time.QuadPart - g_time.QuadPart) / (float)(g_second.QuadPart);
	g_time = time;

	// timeScale
	static float timeScale = 1.f;
	
	if (GetAsyncKeyState(VK_F1) & 0x8000)
	{
		timeScale -= g_deltaTime;
		timeScale = (timeScale < 0.f) ? 0.f : timeScale;
	}
	if (GetAsyncKeyState(VK_F2) & 0x8000)
	{
		timeScale += g_deltaTime;
		timeScale = (timeScale >= 1.f) ? 1.f : timeScale;
	}

	// 플레이어 이동
	float playerSpeed = PLAYER_SPEED * g_deltaTime * timeScale;

	/*if (GetAsyncKeyState('W') & 0x8000)
	{
		g_playerCircle.y -= playerSpeed;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		g_playerCircle.y += playerSpeed;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		g_playerCircle.x -= playerSpeed;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		g_playerCircle.x += playerSpeed;
	}*/

	// 플레이어 회전식 이동
	if (GetAsyncKeyState('A') & 0x8000)
	{
		g_playerAngle -= M_PI * g_deltaTime * timeScale;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		g_playerAngle += M_PI * g_deltaTime * timeScale;
	}
	if (GetAsyncKeyState('W') & 0x8000)
	{
		g_playerCircle.x += playerSpeed * cosf(g_playerAngle);
		g_playerCircle.y += playerSpeed * sinf(g_playerAngle);
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		g_playerCircle.x -= playerSpeed * cosf(g_playerAngle);
		g_playerCircle.y -= playerSpeed * sinf(g_playerAngle);
	}

	// 플레이어 총구 위치
	g_gunPos.x = g_playerCircle.x + cosf(g_playerAngle) * g_gunLength;
	g_gunPos.y = g_playerCircle.y + sinf(g_playerAngle) * g_gunLength;

	// 플레이어 총알 생성
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		Bullet bullet;
		bullet.circle.x = g_gunPos.x + cosf(g_playerAngle) * BULLET_RADIUS;
		bullet.circle.y = g_gunPos.y + sinf(g_playerAngle) * BULLET_RADIUS;
		bullet.circle.r = BULLET_RADIUS;
		bullet.angle = g_playerAngle;
		bullet.dist = 0.f;
		bullet.distLimit = 500.f;

		g_playerBulletList.push_back(bullet);
	}
	
	// 15º 3방향
	if (GetAsyncKeyState('1') & 0x8000)
	{
		float angle = g_playerAngle - M_PI / 12.f;

		for (int i = 0; i < 3; ++i)
		{
			Bullet bullet;
			bullet.circle.x = g_gunPos.x + cosf(g_playerAngle) * BULLET_RADIUS;
			bullet.circle.y = g_gunPos.y + sinf(g_playerAngle) * BULLET_RADIUS;
			bullet.circle.r = BULLET_RADIUS;
			bullet.angle = angle;
			bullet.dist = 0.f;
			bullet.distLimit = 500.f;

			g_playerBulletList.push_back(bullet);

			angle += M_PI / 12.f;
		}
	}

	// 10º 전방향
	if (GetAsyncKeyState('2') & 0x8000)
	{
		float angle = g_playerAngle - M_PI / 18.f;

		for (int i = 0; i < 36; ++i)
		{
			Bullet bullet;
			bullet.circle.x = g_gunPos.x + cosf(g_playerAngle) * BULLET_RADIUS;
			bullet.circle.y = g_gunPos.y + sinf(g_playerAngle) * BULLET_RADIUS;
			bullet.circle.r = BULLET_RADIUS;
			bullet.angle = angle;
			bullet.dist = 0.f;
			bullet.distLimit = 500.f;

			g_playerBulletList.push_back(bullet);

			angle += M_PI / 18.f;
		}
	}

	// 마우스 왼쪽 클릭
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		POINT ptMouse;
		GetCursorPos(&ptMouse);  // 스크린 기준 좌표 반환
		ScreenToClient(g_hWnd, &ptMouse);

		float dx = g_monster.circle.x - ptMouse.x;
		float dy = g_monster.circle.y - ptMouse.y;
		float dist = sqrtf(dx * dx + dy * dy);
		if (dist < g_monster.circle.r)
		{
			MessageBox(NULL, L"몬스터를 클릭했네요", L"앗", MB_OK);
		}
	}

	// 창 크기 확인
	RECT rcWnd;
	GetClientRect(g_hWnd, &rcWnd);
	SetRect(&rcWnd, 0, 0, WND_WIDTH, WND_HEIGHT);

	// 플레이어 창 테두리 이동 제한
	if (g_playerCircle.y - g_playerCircle.r < 0)
	{
		g_playerCircle.y = 0 + g_playerCircle.r;
	}
	if (g_playerCircle.y + g_playerCircle.r > rcWnd.bottom)
	{
		g_playerCircle.y = rcWnd.bottom - g_playerCircle.r;
	}
	if (g_playerCircle.x - g_playerCircle.r < 0)
	{
		g_playerCircle.x = 0 + g_playerCircle.r;
	}
	if (g_playerCircle.x + g_playerCircle.r > rcWnd.right)
	{
		g_playerCircle.x = rcWnd.right - g_playerCircle.r;
	}

	// 몬스터 이동
	g_monster.circle.y += g_monster.dir * g_monster.speed * g_deltaTime * timeScale;
	if (g_monster.circle.y + g_monster.circle.r >= WND_HEIGHT)
	{
		g_monster.circle.y = WND_HEIGHT - g_monster.circle.r;
		g_monster.dir = MV_UP;
	}
	else if (g_monster.circle.y - g_monster.circle.r <= 0)
	{
		g_monster.circle.y = g_monster.circle.r;
		g_monster.dir = MV_DOWN;
	}

	// 몬스터 총알 생성
	g_monster.time += g_deltaTime;
	if (g_monster.time >= g_monster.timeLimit)
	{
		g_monster.time -= g_monster.timeLimit;

		Bullet bullet;
		bullet.circle.x = g_monster.circle.x - g_monster.circle.r - BULLET_RADIUS;
		bullet.circle.y = g_monster.circle.y;
		bullet.circle.r = BULLET_RADIUS;
		bullet.angle = M_PI;
		bullet.dist = 0.f;
		bullet.distLimit = 800.f;

		g_monsterBulletList.push_back(bullet);
	}

	list<Bullet>::iterator iter;
	list<Bullet>::iterator iterEnd = g_playerBulletList.end();
	float bulletSpeed = BULLET_SPEED * g_deltaTime * timeScale;

	// 플레이어 총알 이동
	for (iter = g_playerBulletList.begin(); iter != iterEnd;)
	{
		iter->circle.x += cosf(iter->angle) * bulletSpeed;
		iter->circle.y += sinf(iter->angle) * bulletSpeed;
		iter->dist += bulletSpeed;

		float dx = iter->circle.x - g_monster.circle.x;
		float dy = iter->circle.y - g_monster.circle.y;
		float dist = sqrtf(dx * dx + dy * dy);

		// 몬스터 충돌 처리
		if (dist < iter->circle.r + g_monster.circle.r)
		{
			iter = g_playerBulletList.erase(iter);
			iterEnd = g_playerBulletList.end();
		}
		// 사거리, 화면 밖 총알 제거
		else if (iter->dist >= iter->distLimit || iter->circle.x - iter->circle.r >= WND_WIDTH)
		{
			iter = g_playerBulletList.erase(iter);
			iterEnd = g_playerBulletList.end();
		}
		else
			++iter;
	}
	// 몬스터 총알 이동
	iterEnd = g_monsterBulletList.end();
	for (iter = g_monsterBulletList.begin(); iter != iterEnd;)
	{
		iter->circle.x += cosf(iter->angle) * bulletSpeed;
		iter->circle.y += sinf(iter->angle) * bulletSpeed;
		iter->dist += bulletSpeed;
		float dx = iter->circle.x - g_playerCircle.x;
		float dy = iter->circle.y - g_playerCircle.y;
		float dist = sqrtf(dx * dx + dy * dy);

		// 플레이어 충돌 처리
		if (dist < iter->circle.r + g_playerCircle.r)
		{
			iter = g_monsterBulletList.erase(iter);
			iterEnd = g_monsterBulletList.end();
		}
		// 사거리, 화면 밖 총알 제거
		else if (iter->dist >= iter->distLimit || iter->circle.x + iter->circle.r <= 0)
		{
			iter = g_monsterBulletList.erase(iter);
			iterEnd = g_monsterBulletList.end();
		}
		else
			++iter;
	}

	// 플레이어 출력
	Ellipse(g_hDC, g_playerCircle.x - g_playerCircle.r, g_playerCircle.y - g_playerCircle.r,
		g_playerCircle.x + g_playerCircle.r, g_playerCircle.y + g_playerCircle.r);
	// 총구 출력
	MoveToEx(g_hDC, g_playerCircle.x, g_playerCircle.y, NULL);
	LineTo(g_hDC, g_gunPos.x, g_gunPos.y);
	// 몬스터 출력
	Ellipse(g_hDC, g_monster.circle.x - g_monster.circle.r, g_monster.circle.y - g_monster.circle.r,
		g_monster.circle.x + g_monster.circle.r, g_monster.circle.y + g_monster.circle.r);
	// 플레이어 총알 출력
	iterEnd = g_playerBulletList.end();
	for (iter = g_playerBulletList.begin(); iter != iterEnd; ++iter)
		Ellipse(g_hDC, iter->circle.x - iter->circle.r, iter->circle.y - iter->circle.r,
			iter->circle.x + iter->circle.r, iter->circle.y + iter->circle.r);
	// 몬스터 총알 출력
	iterEnd = g_monsterBulletList.end();
	for (iter = g_monsterBulletList.begin(); iter != iterEnd; ++iter)
		Ellipse(g_hDC, iter->circle.x - iter->circle.r, iter->circle.y - iter->circle.r,
			iter->circle.x + iter->circle.r, iter->circle.y + iter->circle.r);
}  // End of Run()

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다...

    // 전역 문자열 초기화
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI01, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화
    if (!InitInstance(hInstance, nCmdShow))
        return FALSE;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI01));

    MSG msg;

	// For g_deltaTime
	QueryPerformanceFrequency(&g_second);
	QueryPerformanceCounter(&g_time);

    // 기본 메시지 루프
    while (g_isLooping)
    {
		// GetMessage: 메시지가 없으면 blocking 진입
		// PeekMessage: 메시지가 큐에 있으면 true, 없으면 false
		// PM_REMOVE: 메시지 삭제
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		else
		{
			Run();
		}
    }

	ReleaseDC(g_hWnd, g_hDC);

    return (int) msg.wParam;
}

// MyRegisterClass()
// 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI01));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = NULL;  // MAKEINTRESOURCEW(IDC_WINAPI01);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

// InitInstance(HINSTANCE, int)
//
// 이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
// 주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;  // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
      return FALSE;

   // 전역 변수 겟
   g_hWnd = hWnd;
   g_hDC = GetDC(hWnd);

   // 몬스터 초기화
   g_monster.circle.x = WND_WIDTH - MONSTER_RADIUS;
   g_monster.circle.y = MONSTER_RADIUS;
   g_monster.circle.r = MONSTER_RADIUS;
   g_monster.speed = MONSTER_SPEED;
   g_monster.dir = MV_DOWN;
   g_monster.time = 0.f;
   g_monster.timeLimit = 0.6f;

   // 플레이어 총구 
   g_gunPos.x = g_playerCircle.x + cosf(g_playerAngle) * g_gunLength;
   g_gunPos.y = g_playerCircle.y + sinf(g_playerAngle) * g_gunLength;

   // 윈도우 크기 확인
   RECT rc = { 0, 0, WND_WIDTH, WND_HEIGHT };
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
   // 윈도우 크기 설정
   SetWindowPos(hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

// WndProc(HWND, UINT, WPARAM, LPARAM)
//
// 주 창의 메시지를 처리합니다.
//
// WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
// WM_PAINT    - 주 창을 그립니다.
// WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_LBUTTONDOWN:
		// 마우스 위치는 lParam
		// x, y 값 각각 16비트로 32비트 변수에 저장
		// LOWORD, HIWORD 매크로를 이용해 x, y 접근
		if (!g_areaSelection.isStarted)
		{
			g_areaSelection.isStarted = true;
			g_areaSelection.start.x = lParam & 0x0000FFFF;
			g_areaSelection.start.y = lParam >> 16;
			g_areaSelection.end = g_areaSelection.start;

			InvalidateRect(hWnd, NULL, TRUE);  // (hWnd, 지울 영역 Rect, 덮어쓰기 bool)
		}
		break;
	case WM_MOUSEMOVE:
		if (g_areaSelection.isStarted)
		{
			g_areaSelection.end.x = lParam & 0x0000FFFF;
			g_areaSelection.end.y = lParam >> 16;

			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_LBUTTONUP:
		if (g_areaSelection.isStarted) {
			g_areaSelection.isStarted = false;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
			TextOut(hdc, 50, 50, L"안녕하세요", 5);
			Rectangle(hdc, 50, 100, 100, 150);
			Ellipse(hdc, 200, 100, 250, 150);
			MoveToEx(hdc, 300, 100, NULL);
			LineTo(hdc, 350, 150);
			LineTo(hdc, 400, 100);

			TCHAR strMouse[64] = { };
			// 유니코드 문자열 생성
			wsprintf(strMouse, TEXT("x: %d y: %d"), g_areaSelection.start.x, g_areaSelection.start.y);
			TextOut(hdc, 10, 10, strMouse, lstrlen(strMouse));

			if (g_areaSelection.isStarted)
			{
				Rectangle(hdc, g_areaSelection.start.x, g_areaSelection.start.y, g_areaSelection.end.x, g_areaSelection.end.y);
			}
			 
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		g_isLooping = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
