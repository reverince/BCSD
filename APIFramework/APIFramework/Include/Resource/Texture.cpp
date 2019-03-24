#include "Texture.h"
#include "..\Core\PathManager.h"

Texture::Texture() :
	m_hMemDC(NULL), m_hasColorKey(true), m_colorKey(COLORKEY_DEFAULT)
{
}

Texture::~Texture()
{
	// 기존 도구 지정
	SelectObject(m_hMemDC, m_hBitmapOld);

	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}

bool Texture::LoadTexture(HINSTANCE hInst, HDC hDC, const string & key, const wchar_t * pFileName, const string & pathKey)
{
	// 메모리 DC
	m_hMemDC = CreateCompatibleDC(hDC);

	// 파일 경로
	const wchar_t * pPath = GET_SINGLE(PathManager)->FindPath(pathKey);
	wstring strPath;
	
	if (pPath)
		strPath = pPath;

	strPath += pFileName;

	m_hBitmap = (HBITMAP)LoadImage(hInst, strPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// 새 비트맵 도구를 DC에 지정하고 기존 비트맵 도구 저장
	m_hBitmapOld = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	// 핸들에서 비트맵 정보 Get
	GetObject(m_hBitmap, sizeof(m_bitmapInfo), &m_bitmapInfo);

	return true;
}
