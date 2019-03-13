// WinAPI01.cpp : 응용 프로그램 진입점 정의
//

#include "stdafx.h"
#include "WinAPI01.h"

#define MAX_LOADSTRING 100

struct AreaSelection  // 마우스 드래그 영역 표시
{
	bool isStarted;
	POINT start;
	POINT end;
};

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름
AreaSelection areaSelection;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI01));

    MSG msg;

    // 기본 메시지 루프
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

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
   {
      return FALSE;
   }

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
	case WM_LBUTTONDOWN:  // 마우스 왼쪽 클릭
		// 마우스 위치는 lParam
		// x, y 값 각각 16비트로 32비트 변수에 저장
		// LOWORD, HIWORD 매크로 이용해 x, y 접근
		if (!areaSelection.isStarted)
		{
			areaSelection.isStarted = true;
			areaSelection.start.x = lParam & 0x0000FFFF;
			areaSelection.start.y = lParam >> 16;
			areaSelection.end = areaSelection.start;

			InvalidateRect(hWnd, NULL, TRUE);  // (hWnd, 지울 영역 Rect, 덮어쓰기 bool)
		}
		break;
	case WM_MOUSEMOVE:
		if (areaSelection.isStarted)
		{
			areaSelection.end.x = lParam & 0x0000FFFF;
			areaSelection.end.y = lParam >> 16;

			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_LBUTTONUP:
		if (areaSelection.isStarted) {
			areaSelection.isStarted = false;
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
			Rectangle(hdc, 100, 100, 150, 150);
			Ellipse(hdc, 200, 100, 250, 150);
			MoveToEx(hdc, 300, 100, NULL);
			LineTo(hdc, 350, 150);
			LineTo(hdc, 400, 100);

			TCHAR strMouse[64] = { };
			// 유니코드 문자열 생성
			wsprintf(strMouse, TEXT("x: %d y: %d"), areaSelection.start.x, areaSelection.start.y);
			TextOut(hdc, 600, 30, strMouse, lstrlen(strMouse));

			if (areaSelection.isStarted)
			{
				Rectangle(hdc, areaSelection.start.x, areaSelection.start.y, areaSelection.end.x, areaSelection.end.y);
			}
			 
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
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
