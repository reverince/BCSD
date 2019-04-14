#include "SceneManager.h"
#include "StartScene.h"
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
	if (!CreateScene<StartScene>(SC_CURRENT))
		return false;

	return true;
}

void SceneManager::Input(float deltaTime)
{
	m_pScene->Input(deltaTime);
}

int SceneManager::Update(float deltaTime)
{
	m_pScene->Update(deltaTime);
	return 0;
}

int SceneManager::LateUpdate(float deltaTime)
{
	m_pScene->LateUpdate(deltaTime);
	return 0;
}

void SceneManager::Collision(float deltaTime)
{
	m_pScene->Collision(deltaTime);
}

void SceneManager::Render(HDC hDC, float deltaTime)
{
	m_pScene->Render(hDC, deltaTime);
}
