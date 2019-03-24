#pragma once
#include "..\Game.h"

class CollisionManager
{
	DECLARE_SINGLE(CollisionManager);

	list<class Object *> m_listObj;

public:

	void AddObject(class Object * pObj);

	void Collision(float deltaTime);
	bool Collision(float deltaTime, class Object * pSrc, class Object * pDest);
};
