#include "SceneManager.h"
#include "InGameScene.h"

DEFINE_SINGLE(SceneManager);

SceneManager::SceneManager() :
	m_pScene(nullptr)
{
}

SceneManager::~SceneManager()
{
	SAFE_DELETE(m_pScene);
}

bool SceneManager::Init()
{
	CreateScene<InGameScene>(SC_CURRENT);

	return true;
}
