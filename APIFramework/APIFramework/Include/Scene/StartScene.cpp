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

void StartScene::StartButtonCallback(float time)
{
}

void StartScene::QuitButtonCallback(float time)
{
	GET_SINGLE(Core)->DestroyGame();
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

	POSITION size;

	UIButton* pStartBtn = Object::CreateObject<UIButton>("StartButton", pLayerUI);
	pStartBtn->SetPos(WND_WIDTH / 2 - BUTTON_WIDTH, WND_HEIGHT / 2 + BUTTON_HEIGHT);
	pStartBtn->SetSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	pStartBtn->SetTexture("StartButton", START_BUTTON_TEXTURE);
	ColliderRect* pStartColl = (ColliderRect*)pStartBtn->GetCollider("ButtonBody");
	size = pStartBtn->GetSize();
	pStartColl->SetRect(-0.5f * size.x, -0.5f * size.y, 0.5f * size.x, 0.5f * size.y);
	pStartColl->AddCollisionFunc(CS_ENTER, pStartBtn, &UIButton::MouseOn);
	pStartColl->AddCollisionFunc(CS_LEAVE, pStartBtn, &UIButton::MouseOff);
	pStartBtn->SetCallback(this, &StartScene::StartButtonCallback);

	SAFE_RELEASE(pStartColl);
	SAFE_RELEASE(pStartBtn);

	UIButton* pQuitBtn = Object::CreateObject<UIButton>("QuitButton", pLayerUI);
	pQuitBtn->SetPos(WND_WIDTH / 2 + BUTTON_WIDTH, WND_HEIGHT / 2 + BUTTON_HEIGHT);
	pQuitBtn->SetSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	pQuitBtn->SetTexture("QuitButton", QUIT_BUTTON_TEXTURE);
	ColliderRect* pQuitColl = (ColliderRect*)pQuitBtn->GetCollider("ButtonBody");
	size = pQuitBtn->GetSize();
	pQuitColl->SetRect(-0.5f * size.x, -0.5f * size.y, 0.5f * size.x, 0.5f * size.y);
	pQuitColl->AddCollisionFunc(CS_ENTER, pQuitBtn, &UIButton::MouseOn);
	pQuitColl->AddCollisionFunc(CS_LEAVE, pQuitBtn, &UIButton::MouseOff);
	pQuitBtn->SetCallback(this, &StartScene::QuitButtonCallback);

	SAFE_RELEASE(pQuitColl);
	SAFE_RELEASE(pQuitBtn);

	return true;
}
