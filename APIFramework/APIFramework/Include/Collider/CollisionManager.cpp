#include "CollisionManager.h"
#include "..\Object\Object.h"
#include "Collider.h"

DEFINE_SINGLE(CollisionManager);

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::AddObject(Object * pObj)
{
	if (pObj->HasCollider())
	{
		m_listObj.push_back(pObj);
	}
}

void CollisionManager::Collision(float deltaTime)
{
	if (m_listObj.size() < 2)
	{
		m_listObj.clear();
		return;
	}

	// �浹 ó��
	list<Object *>::iterator iterEnd = --(m_listObj.end());
	--iterEnd;
	for (list<Object *>::iterator iter = m_listObj.begin(); iter != iterEnd; ++iter)
	{
		list<Object *>::iterator iter2 = iter;
		for (++iter2; iter2 != m_listObj.end(); ++iter2)
			Collision(deltaTime, *iter, *iter2);
	}

	m_listObj.clear();
}

bool CollisionManager::Collision(float deltaTime, Object * pSrc, Object * pDest)
{
	const list<Collider *> * pListSrc = pSrc->GetColliders();
	const list<Collider *> * pListDest = pDest->GetColliders();

	bool isCollided = false;
	list<Collider *>::const_iterator iterSrc;
	list<Collider *>::const_iterator iterDest;
	for (iterSrc = pListSrc->begin(); iterSrc != pListSrc->end(); ++iterSrc)
	{
		for (iterDest = pListDest->begin(); iterDest != pListDest->end(); ++iterDest)
		{
			isCollided = (*iterSrc)->Collision(*iterDest);

			if (isCollided)
			{
				// �浹 ���� ����
				(*iterDest)->SetHitPoint((*iterSrc)->GetHitPoint());

				// �浹
				if (!(*iterSrc)->CheckCollision(*iterDest))
				{
					// ���� ������ �浹 ����Ʈ�� �߰�
					(*iterSrc)->AddCollision(*iterDest);
					(*iterDest)->AddCollision(*iterSrc);

					// �浹 �Լ� ȣ��
					(*iterSrc)->CallFunc(CS_ENTER, deltaTime, *iterDest);
					(*iterDest)->CallFunc(CS_ENTER, deltaTime, *iterSrc);
				}
				// �浹 ����
				else
				{
					(*iterSrc)->CallFunc(CS_STAY, deltaTime, *iterDest);
					(*iterDest)->CallFunc(CS_STAY, deltaTime, *iterSrc);
				}
			}
			// �浹 ����
			else if ((*iterSrc)->CheckCollision(*iterDest))
			{
				(*iterSrc)->EraseCollision(*iterDest);
				(*iterDest)->EraseCollision(*iterSrc);

				(*iterSrc)->CallFunc(CS_LEAVE, deltaTime, *iterDest);
				(*iterDest)->CallFunc(CS_LEAVE, deltaTime, *iterSrc);
			}
		}
	}

	return false;
}
