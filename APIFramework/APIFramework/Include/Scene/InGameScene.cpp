#include "InGameScene.h"
#include "..\Core\Camera.h"
#include "Layer.h"
#include "..\Object\Stage.h"
#include "..\Object\Player.h"
#include "..\Object\Minion.h"
#include "..\Object\Bullet.h"
#include "..\Collider\ColliderPixel.h"

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

	Layer * pLayerStage = FindLayer("Stage");
	Stage * pStage = Object::CreateObject<Stage>("Stage", pLayerStage);

	ColliderPixel * pCollPixel = pStage->AddCollider<ColliderPixel>("StageColl");
	pCollPixel->SetPixels((char *)STAGE_TEXTURE);

	Layer * pLayerDefault = FindLayer("Default");
	Player * pPlayer = Object::CreateObject<Player>("Player", pLayerDefault);
	Minion * pMinion = Object::CreateObject<Minion>("Minion", pLayerDefault);
	Bullet * pBullet = Scene::CreatePrototype<Bullet>("Bullet");

	GET_SINGLE(Camera)->SetTarget(pPlayer);

	SAFE_RELEASE(pCollPixel);
	SAFE_RELEASE(pStage);
	SAFE_RELEASE(pPlayer);
	SAFE_RELEASE(pMinion);
	SAFE_RELEASE(pBullet);

	return true;
}
