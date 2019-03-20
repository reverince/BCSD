#include "InGameScene.h"
#include "Layer.h"
#include "../Object/Player.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

bool InGameScene::Init()
{
	if (!Scene::Init())
		return false;

	Layer * pLayer = FindLayer("Default");
	Player * pPlayer = Object::CreateObject<Player>("Player", pLayer);

	SAFE_RELEASE(pPlayer);

	return true;
}
