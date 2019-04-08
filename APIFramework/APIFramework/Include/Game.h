#pragma once
#pragma comment(lib, "msimg32")

#include <Windows.h>
#include <conio.h>
#include <crtdbg.h>  // �޸� ���� üũ
#include <functional>
#include <list>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>
#include "Macro.h"
#include "Flag.h"
#include "Types.h"
#include "resource.h"
using namespace std;

template <typename T>
void SafeDeleteVectorList(T & p)
{
	for (typename T::iterator iter = p.begin(); iter != p.end(); ++iter)
		SAFE_DELETE(*iter);

	p.clear();
}

template <typename T>
void SafeReleaseVectorList(T & p)
{
	for (typename T::iterator iter = p.begin(); iter != p.end(); ++iter)
		SAFE_RELEASE(*iter);

	p.clear();
}

template <typename T>
void SafeDeleteMap(T & p)
{
	for (typename T::iterator iter = p.begin(); iter != p.end(); ++iter)
		SAFE_DELETE(iter->second);

	p.clear();
}

template <typename T>
void SafeReleaseMap(T & p)
{
	for (typename T::iterator iter = p.begin(); iter != p.end(); ++iter)
		SAFE_RELEASE(iter->second);

	p.clear();
}
