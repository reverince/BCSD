#pragma once

#define PI 3.141592f
#define CLASS_NAME L"WinAPI02"
#define WND_WIDTH 1600
#define WND_HEIGHT 900

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