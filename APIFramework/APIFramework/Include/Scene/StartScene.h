#pragma once
#include "Scene.h"

class StartScene : public Scene
{
	friend class SceneManager;

	StartScene();
	~StartScene();

public:

	virtual bool Init();
};
