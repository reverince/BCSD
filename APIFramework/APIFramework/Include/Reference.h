#pragma once
#include "Game.h"

class Reference
{
protected:

	int m_refCnt;
	bool m_isAlive;
	bool m_isEnabled;
	string m_tag;

	Reference();
	virtual ~Reference() = 0;

public:

	string GetTag() const { return m_tag; }
	void SetTag(const string & tag) { m_tag = tag; }

	void AddRef() { ++m_refCnt; }
	void Release()
	{
		--m_refCnt;
		if (m_refCnt == 0)
			delete this;
	}

	void SetEnabled(bool enable) { m_isEnabled = enable; }
	bool IsEnabled() const { return m_isEnabled; }
	void Die() { m_isAlive = false; }
	bool IsAlive() const { return m_isAlive; }
};
