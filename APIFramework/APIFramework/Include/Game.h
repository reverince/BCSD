#pragma once
#include "Flag.h"
#include "Macro.h"
#include "Types.h"
#include "resource.h"
#include <Windows.h>
#include <list>
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