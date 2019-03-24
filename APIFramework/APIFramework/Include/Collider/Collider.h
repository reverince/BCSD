#pragma once
#include "..\Reference.h"

class Collider : public Reference
{
protected:

	friend class Object;

	COLLIDER_TYPE m_type;
	class Object * m_pObj;
	list<Collider *> m_listCollision;
	list<function<void(float, Collider *, Collider *)>> m_listFunc[CS_END];  // 함수 리스트의 배열

	Collider();
	Collider(const Collider & collider);
	virtual ~Collider() = 0;

	bool CollisionRectVsRect(const RECTANGLE & src, const RECTANGLE & dest);

public:

	void SetObj(class Object * pObj) { m_pObj = pObj; }
	COLLIDER_TYPE GetType() const { return m_type; }
	class Object * GetObj() const { return m_pObj; }

	void AddCollision(Collider * pCollider) { m_listCollision.push_back(pCollider); }
	bool CheckCollision(Collider * pCollider)
	{
		for (list<Collider *>::iterator iter = m_listCollision.begin(); iter != m_listCollision.end(); ++iter)
		{
			if (*iter == pCollider)
				return true;
		}

		return false;
	}
	void EraseCollision(Collider * pCollider)
	{
		for (list<Collider *>::iterator iter = m_listCollision.begin(); iter != m_listCollision.end(); ++iter)
		{
			if (*iter == pCollider)
			{
				m_listCollision.erase(iter);
				break;
			}
		}
	}

	void AddCollisionFunc(COLLISION_STATE state, void(*pFunc)(float, Collider *, Collider *))
	{
		function<void(float, Collider *, Collider *)> func;
		func = bind(pFunc, placeholders::_1, placeholders::_2, placeholders::_3);
		m_listFunc[state].push_back(func);
	}

	template <typename T>
	void AddCollisionFunc(COLLISION_STATE state, T * pObj, void(T::*pFunc)(float, Collider *, Collider *))
	{
		function<void(float, Collider *, Collider *)> func;
		func = bind(pFunc, pObj, placeholders::_1, placeholders::_2, placeholders::_3);
		m_listFunc[state].push_back(func);
	}

	void CallFunc(COLLISION_STATE state, float deltaTime, Collider * pDest)
	{
		list< function<void(float, Collider *, Collider *)> >::iterator iter;
		for (iter = m_listFunc[state].begin(); iter != m_listFunc[state].end(); ++iter)
		{
			(*iter)(deltaTime, this, pDest);
		}
	}

	virtual bool Init();
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual bool Collision(Collider * pDest);
	virtual void Render(HDC hDC, float deltaTime);
	virtual Collider * Clone() = 0;
};

