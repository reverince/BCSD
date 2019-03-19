#pragma once
#include "Scene.h"

class InGameScene : public Scene
{
	friend class SceneManager;

	InGameScene();
	~InGameScene();

public:

	virtual bool Init();
};
