#include "StartScene.h"
#include "..\Core\Core.h"
#include "..\Core\Camera.h"
#include "Layer.h"
#include "..\Object\Stage.h"
#include "..\Object\UIPanel.h"
#include "..\Object\UIButton.h"
#include "..\Collider\ColliderRect.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::Init()
{
	if (!Scene::Init())
		return false;

	Layer* pLayerUI = FindLayer("UI");

	UIPanel* pBackPanel = Object::CreateObject<UIPanel>("BackPanel", pLayerUI);
	pBackPanel->SetSize(WND_WIDTH, WND_HEIGHT);
	pBackPanel->SetTexture("StartBack", START_BACK_TEXTURE);

	SAFE_RELEASE(pBackPanel);

	POSITION pos, size;

	UIButton* pStartBtn = Object::CreateObject<UIButton>("StartButton", pLayerUI);
	pStartBtn->SetPos(WND_WIDTH / 2 - BUTTON_WIDTH, WND_HEIGHT / 2 + BUTTON_HEIGHT);
	pStartBtn->SetSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	pStartBtn->SetTexture("StartButton", START_BUTTON_TEXTURE);
	ColliderRect* pStartColl = (ColliderRect*)pStartBtn->GetCollider("ButtonBody");
	pos = pStartBtn->GetPos();
	size = pStartBtn->GetSize();
	pStartColl->SetRect(pos.x, pos.y, pos.x + size.x, pos.y + size.y);

	SAFE_RELEASE(pStartColl);
	SAFE_RELEASE(pStartBtn);

	UIButton* pQuitBtn = Object::CreateObject<UIButton>("QuitButton", pLayerUI);
	pQuitBtn->SetPos(WND_WIDTH / 2 + BUTTON_WIDTH, WND_HEIGHT / 2 + BUTTON_HEIGHT);
	pQuitBtn->SetSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	pQuitBtn->SetTexture("QuitButton", QUIT_BUTTON_TEXTURE);
	ColliderRect* pQuitColl = (ColliderRect*)pQuitBtn->GetCollider("ButtonBody");
	pos = pQuitBtn->GetPos();
	size = pQuitBtn->GetSize();
	pQuitColl->SetRect(pos.x, pos.y, pos.x + size.x, pos.y + size.y);

	SAFE_RELEASE(pQuitColl);
	SAFE_RELEASE(pStartBtn);

	return true;
}
