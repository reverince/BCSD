#include "pch.h"
#include "StageManager.h"
#include "Stage.h"

StageManager * StageManager::pInst = nullptr;

StageManager::StageManager() :
	pCurStage(nullptr)
{
}

StageManager::~StageManager()
{
}

bool StageManager::init()
{
	pCurStage = new Stage;

	if (!pCurStage->init()) return false;

	return true;
}

void StageManager::run()
{
	pCurStage->render();
}
