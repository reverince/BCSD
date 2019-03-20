#pragma once
#include "Game.h"

class Reference
{
protected:

	int m_refCnt;

	Reference();
	virtual ~Reference() = 0;

public:

	void AddRef() { ++m_refCnt; }
	void Release()
	{
		--m_refCnt;
		if (m_refCnt == 0)
			delete this;
	}
};
