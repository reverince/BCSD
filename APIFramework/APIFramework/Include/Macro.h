#pragma once

#define CLASS_NAME L"WinAPI02"
#define WND_WIDTH 800
#define WND_HEIGHT 600

#define SAFE_DELETE(p) if (p) { delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY(p) if p { delete[] p; p = nullptr; }

// ΩÃ±€≈Ê
//#define DECLARE_SINGLE