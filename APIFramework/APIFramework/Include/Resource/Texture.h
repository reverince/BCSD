#pragma once
#include "..\Reference.h"

class Texture : public Reference
{
	friend class ResourceManager;

	HDC m_hMemDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hBitmapOld;
	BITMAP m_bitmapInfo;

	Texture();
	~Texture();

public:

	HDC GetDC() const { return m_hMemDC; }

	bool LoadTexture(HINSTANCE hInst, HDC hDC, const string & key, const wchar_t * pFileName, const string & pathKey = PATH_TEXTURE);
};
