#include "framework.h"
#include "CSceneManager.h"

#include "CScene.h"
#include "CSceneTitle.h"
#include "CSceneTileTool.h"
#include "CSceneStage01.h"
#include "CSceneState02.h"
#include "CEndingStage.h"
#include "COpenScene.h"
#include "EndingScene.h"
#include "CBonusMap.h"

CSceneManager::CSceneManager()
{
	m_pCurScene = nullptr;
}

CSceneManager::~CSceneManager()
{
}

void CSceneManager::Init()
{
	// TODO : ���ӿ� �ʿ��� �� �߰�
	// ���Ӿ����� �ڷᱸ���� �߰�
	CScene* pSceneTitle = new CSceneTitle();
	m_mapScene.insert(make_pair(GroupScene::Title, pSceneTitle));
	CSceneTileTool* pSceneTileTool = new CSceneTileTool;
	m_mapScene.insert(make_pair(GroupScene::TileTool, pSceneTileTool));
	CScene* pSceneStage01 = new CSceneStage01();
	m_mapScene.insert(make_pair(GroupScene::Stage01, pSceneStage01));
	CScene* pSceneStage02 = new CSceneState02();
	m_mapScene.insert(make_pair(GroupScene::Stage02, pSceneStage02));
	CScene* pBonusMap = new CBonusMap();
	m_mapScene.insert(make_pair(GroupScene::Bonus, pBonusMap));

	CScene* pOpenstage = new COpenScene();
	m_mapScene.insert(make_pair(GroupScene::Opne, pOpenstage));

	CScene* pEndingScene = new CEndingStage();
	m_mapScene.insert(make_pair(GroupScene::End, pEndingScene));

	// ���Ӿ� �ڷᱸ���� ��ȸ�ϸ� ���� �ʱ�ȭ
	for (pair<GroupScene, CScene*> scene : m_mapScene)
	{
		scene.second->SceneInit();
	}

	// ���� ó������ �����ؾ��� ���Ӿ� ����
	m_pCurScene = pSceneTitle;
	m_pCurScene->SceneEnter();
}

void CSceneManager::Update()
{
	m_pCurScene->SceneUpdate();
	m_pCurScene->ScenePhysicsUpdate();
}

void CSceneManager::Render()
{
	m_pCurScene->SceneRender();
}

void CSceneManager::Release()
{
	// ���Ӿ� �ڷᱸ���� ��ȸ�ϸ� �����Ҵ�� ���� ����
	for (pair<GroupScene, CScene*> scene : m_mapScene)
	{
		scene.second->SceneRelease();
		delete scene.second;
	}
	
	// ��� �����Ҵ�� ���� �����ѵ� �ڷᱸ���� clear
	m_mapScene.clear();
}

void CSceneManager::ChangeScene(GroupScene scene)
{
	// �������� Exit, �������� Enter
	m_pCurScene->SceneExit();
	m_pCurScene = m_mapScene[scene];
	m_pCurScene->SceneEnter();
}

CScene* CSceneManager::GetCurScene()
{
	return m_pCurScene;
}
