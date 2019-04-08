#pragma once
#include "..\Reference.h"

class Texture : public Reference
{
	friend class ResourceManager;

	HDC m_hMemDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hBitmapOld;
	BITMAP m_bitmapInfo;
	bool m_hasColorKey;
	COLORREF  m_colorKey;

	Texture();
	~Texture();

public:

	void SetColorKey(UCHAR r, UCHAR g, UCHAR b) { m_colorKey = RGB(r, g, b); m_hasColorKey = true; }
	void SetColorKey(COLORREF colorKey) { m_colorKey = colorKey; m_hasColorKey = true; }
	COLORREF GetColorKey() const { return m_colorKey; }
	bool HasColorKey() const { return m_hasColorKey; }

	long GetWidth() const { return m_bitmapInfo.bmWidth; }
	long GetHeight() const { return m_bitmapInfo.bmHeight; }

	HDC GetDC() const { return m_hMemDC; }

	bool LoadTexture(HINSTANCE hInst, HDC hDC, const string & key, const wchar_t * pFileName, const string & pathKey = PATH_TEXTURE);
};
