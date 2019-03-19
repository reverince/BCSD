#pragma once

#define CLASS_NAME L"WinAPI02"
#define WND_WIDTH 1280
#define WND_HEIGHT 720

#define SAFE_DELETE(p) if (p) { delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY(p) if p { delete[] p; p = nullptr; }

// ΩÃ±€≈Ê

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

#define DEFINE_SINGLE(Type) Type * Type::m_pInst = nullptr;
#define GET_SINGLE(Type) Type::GetInst()
#define DESTROY_SINGLE(Type) Type::DestroyInst()
