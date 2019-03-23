#pragma once
#include "..\Game.h"

class PathManager
{
	DECLARE_SINGLE(PathManager);

	unordered_map<string, wstring> m_mapPath;

public:

	bool Init();
	bool CreatePath(const string & key, const wchar_t * pPath, const string & baseKey = PATH_ROOT);
	const wchar_t * FindPath(const string & key);
};
