#include "InGameScene.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

bool InGameScene::Init()
{
	// 부모 클래스 Scene의 Init() 호출
	if (!Scene::Init())
		return false;

	return false;
}
