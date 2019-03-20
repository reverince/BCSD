#pragma once
#include "../Game.h"

class SceneManager
{
	class Scene * m_pScene;
	class Scene * m_pSceneNext;

	DECLARE_SINGLE(SceneManager);

public:

	bool Init();
	void Input(float deltaTime);
	int Update(float deltaTime);
	int LateUpdate(float deltaTime);
	void Collision(float deltaTime);
	void Render(HDC hDC, float deltaTime);

	template <typename T>
	T * CreateScene(SCENE_CREATE sc)
	{
		T * pScene = new T;

		if (!pScene->Init())
		{
			SAFE_DELETE(pScene);
			return nullptr;
		}

		switch (sc)
		{
		case SC_CURRENT:
			SAFE_DELETE(m_pScene);
			m_pScene = pScene;
			break;
		case SC_NEXT:
			SAFE_DELETE(m_pSceneNext);
			m_pSceneNext = pScene;
			break;
		}

		return pScene;
	};
};
