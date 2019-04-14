#pragma once
#include "Scene.h"

class StartScene : public Scene
{
	friend class SceneManager;

	StartScene();
	~StartScene();

public:

	void StartButtonCallback(float time);
	void QuitButtonCallback(float time);

	virtual bool Init();
};
