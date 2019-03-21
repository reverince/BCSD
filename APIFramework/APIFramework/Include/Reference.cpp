#include "Reference.h"

Reference::Reference() :
	m_refCnt(1), m_isAlive(true), m_isEnabled(true)
{
}

Reference::~Reference()
{
}
