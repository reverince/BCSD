#pragma once
#include "..\Game.h"

class ResourceManager
{
	DECLARE_SINGLE(ResourceManager);

	HINSTANCE m_hInst;
	HDC m_hDC;
	unordered_map<string, class Texture *> m_mapTexture;

public:

	bool Init(HINSTANCE hInst, HDC hDC);
	class Texture * LoadTexture(const string & key, const wchar_t * pFileName, const string & pathKey = PATH_TEXTURE);
	class Texture * FindTexture(const string & key);
};
