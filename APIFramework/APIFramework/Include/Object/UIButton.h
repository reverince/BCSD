#pragma once
#include "UI.h"

class UIButton : public UI
{
	friend class Object;
	friend class Scene;

	UIButton();
	UIButton(const UIButton& ui);
	~UIButton();

	function<void(float time)> m_callback;
	bool m_isCallbackEnabled;

public:

	template <typename T>
	void SetCallback(T* pObj, void (T::* pFunc)(float))
	{
		m_callback = bind(pFunc, pObj, placeholders::_1);
		m_isCallbackEnabled = true;
	}

	void SetCallback(void(*pFunc)(float))
	{
		m_callback = bind(pFunc, placeholders::_1);
		m_isCallbackEnabled = true;
	}

	void MouseOn(float deltaTime, class Collider* pSrc, class Collider* pDest);
	void MouseOff(float deltaTime, class Collider* pSrc, class Collider* pDest);

	virtual bool Init();
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual void Collision(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	virtual UIButton* Clone();
};
