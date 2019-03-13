# WinAPI 2D 게임 제작

참고: [WINAPI 2D 게임제작](https://www.youtube.com/playlist?list=PL4SIC1d_ab-YhAo-VE51_yxBHd6yZOFHu) - 어소트락 게임아카데미

- `WCHAR` : `typedef wchar_t WCHAR;  // 16-bit UNICODE char`
- `TCHAR` : `typedef WCHAR TCHAR;`

### `wWinMain` 

```cpp

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
```

- 엔트리 함수 (Win32의 `main`)
- `APIENTRY`
  ```cpp
  #define WINAPI __stdcall
  #define WINAPIV __cdecl
  #define APIENTRY WINAPI
  ```
  - [C++ 함수 호출 규약](http://confluence.goldpitcher.co.kr/pages/viewpage.action?pageId=26378616)
- `HINSTANCE` : 인스턴스 핸들 (`int` 또는 `void*`)

### `WndProc`

주 창의 메시지 처리

- `InvalidateRect(HWND hWnd, const RECT *lpRect, BOOL bErase)` : 화면 갱신

#### `WM_PAINT`

- `TextOut(HDC hdc, int x, int y, LPCWSTR lpString, int c)` : 지정 위치에 `c`글자의 유니코드 문자열 `lpString` 출력
- `Rectangle(HDC hdc, int left, int top, int right, int bottom)` : 사각형 출력
- `Ellipse(HDC hdc, int left, int top, int right, int bottom)` : 원 출력
- `MoveToEx(HDC hdc, int x, int y, LPPOINT lppt)`
- `LineTo(HDC hdc, int x, int y)`

```cpp
TCHAR strMouse[64] = { };
// 유니코드 문자열 생성
wsprintf(strMouse, TEXT("x: %d y: %d"), area.start.x, area.start.y);
TextOut(hdc, 600, 30, strMouse, lstrlen(strMouse));
```
