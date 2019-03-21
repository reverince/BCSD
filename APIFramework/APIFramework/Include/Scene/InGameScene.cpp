#include "InGameScene.h"
#include "Layer.h"
#include "..\Object\Player.h"
#include "..\Object\Minion.h"
#include "..\Object\Bullet.h"

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
	Minion * pMinion = Object::CreateObject<Minion>("Minion", pLayer);
	Bullet * pBullet = Scene::CreatePrototype<Bullet>("Bullet");

	SAFE_RELEASE(pPlayer);
	SAFE_RELEASE(pMinion);
	SAFE_RELEASE(pBullet);

	return true;
}
