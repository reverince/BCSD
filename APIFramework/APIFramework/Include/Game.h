#pragma once
#pragma comment(lib, "msimg32")
#include "Flag.h"
#include "Macro.h"
#include "Types.h"
#include "resource.h"
#include <Windows.h>
#include <crtdbg.h>  // 메모리 누수 체크
#include <functional>
#include <list>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>
using namespace std;

template <typename T>
void SafeDeleteVectorList(T & p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE(*iter);
	}

	p.clear();
}

template <typename T>
void SafeReleaseVectorList(T & p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_RELEASE(*iter);
	}

	p.clear();
}

template <typename T>
void SafeDeleteMap(T & p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	p.clear();
}

template <typename T>
void SafeReleaseMap(T & p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_RELEASE(iter->second);
	}

	p.clear();
}
