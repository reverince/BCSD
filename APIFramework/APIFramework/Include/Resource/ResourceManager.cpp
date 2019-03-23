#include "ResourceManager.h"
#include "Texture.h"

DEFINE_SINGLE(ResourceManager);

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	SafeReleaseMap(m_mapTexture);
	SAFE_RELEASE(m_pBackBuffer);
}

bool ResourceManager::Init(HINSTANCE hInst, HDC hDC)
{
	m_hInst = hInst;
	m_hDC = hDC;

	// ¹é ¹öÆÛ
	m_pBackBuffer = LoadTexture("BackBuffer", L"back_buffer.bmp");

	return true;
}

Texture * ResourceManager::LoadTexture(const string & key, const wchar_t * pFileName, const string & pathKey)
{
	Texture * pTexture = FindTexture(key);

	if (pTexture)
		return pTexture;

	pTexture = new Texture;

	if (!pTexture->LoadTexture(m_hInst, m_hDC, key, pFileName, pathKey))
	{
		SAFE_RELEASE(pTexture);
		return nullptr;
	}

	pTexture->AddRef();
	m_mapTexture.insert(make_pair(key, pTexture));

	return pTexture;
}

Texture * ResourceManager::FindTexture(const string & key)
{
	unordered_map<string, class Texture *>::iterator iter = m_mapTexture.find(key);

	if (iter == m_mapTexture.end())
		return nullptr;

	iter->second->AddRef();

	return iter->second;
}
