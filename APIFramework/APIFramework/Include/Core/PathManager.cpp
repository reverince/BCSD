#include "PathManager.h"

DEFINE_SINGLE(PathManager);

PathManager::PathManager()
{
}

PathManager::~PathManager()
{
}

bool PathManager::Init()
{
	wchar_t strPath[MAX_PATH] = { };

	GetModuleFileName(NULL, strPath, MAX_PATH);

	// 실행 파일 이름 제거
	for (int i = lstrlen(strPath) - 1; i >= 0; --i)
	{
		if (strPath[i] == '/' || strPath[i] == '\\')
		{
			memset(strPath + (i + 1), 0, sizeof(wchar_t) * (MAX_PATH - (i + 1)));
			break;
		}
	}

	m_mapPath.insert(make_pair(PATH_ROOT, strPath));

	// Textures 패스 생성
	if (!CreatePath(PATH_TEXTURE, L"textures\\"))
		return false;

	return true;
}

bool PathManager::CreatePath(const string & key, const wchar_t * pPath, const string & baseKey)
{
	const wchar_t * pBasePath = FindPath(baseKey);
	wstring strPath;

	if (pBasePath)
		strPath = pBasePath;

	strPath += pPath;

	m_mapPath.insert(make_pair(key, strPath));

	return true;
}

const wchar_t * PathManager::FindPath(const string & key)
{
	unordered_map<string, wstring>::iterator iter = m_mapPath.find(key);

	if (iter == m_mapPath.end())
		return nullptr;

	return iter->second.c_str();
}

const char * PathManager::FindPathMultiByte(const string & key)
{
	const wchar_t * pPath = FindPath(key);

	if (!pPath)
		return nullptr;

	memset(m_path, 0, sizeof(char) * MAX_PATH);

	WideCharToMultiByte(CP_ACP, 0, pPath, -1, m_path, lstrlen(pPath), 0, 0);

	return m_path;
}
