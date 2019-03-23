#pragma once

#define CLASS_NAME L"WinAPI02"
#define WND_WIDTH 1600
#define WND_HEIGHT 900
#define PATH_ROOT "RootPath"
#define PATH_TEXTURE "TexturePath"

#define PLAYER_WIDTH 100.f
#define PLAYER_HEIGHT PLAYER_WIDTH
#define PLAYER_SPEED 500.f
#define PLAYER_TEXTURE_NORMAL L"trump_normal.bmp"
#define MINION_WIDTH 50.f
#define MINION_HEIGHT MINION_WIDTH
#define MINION_SPEED 300.f
#define BULLET_WIDTH 20.f
#define BULLET_HEIGHT BULLET_WIDTH
#define BULLET_SPEED 1000.f

#define PI 3.141592f

#define SAFE_DELETE(p) if (p) { delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY(p) if p { delete[] p; p = nullptr; }
#define SAFE_RELEASE(p) if (p) { (p)->Release(); p = nullptr; }

// ½Ì±ÛÅæ
#define DECLARE_SINGLE(Type)\
private:\
	static Type * m_pInst;\
	Type();\
	~Type();\
public:\
	static Type * GetInst()\
	{\
		if (!m_pInst)\
			m_pInst = new Type;\
		return m_pInst;\
	}\
	static void DestroyInst()\
	{\
		SAFE_DELETE(m_pInst);\
	}\
private:

#define DEFINE_SINGLE(Type) Type * Type::m_pInst = nullptr
#define GET_SINGLE(Type) Type::GetInst()
#define DESTROY_SINGLE(Type) Type::DestroyInst()

#define GET_RESOLUTION Core::GetInst()->GetResolution()
