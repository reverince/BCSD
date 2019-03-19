#pragma once
#include "..\Game.h"

class Object
{
protected:
	POSITION m_pos;
	_SIZE m_size;

	Object();
	virtual ~Object();
};
