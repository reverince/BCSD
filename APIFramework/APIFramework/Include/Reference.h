#pragma once
#include "Game.h"

class Reference
{
protected:

	int m_refCnt;
	bool m_isAlive;
	bool m_isEnabled;

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

	void SetEnabled(bool enable) { m_isEnabled = enable; }
	bool GetEnabled() const { return m_isEnabled; }
	void Die() { m_isAlive = false; }
	bool IsAlive() const { return m_isAlive; }
};
