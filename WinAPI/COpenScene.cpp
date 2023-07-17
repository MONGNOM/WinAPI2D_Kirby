#include "framework.h"
#include "COpenScene.h"
#include "WinAPI.h"

#include "CRenderManager.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"


COpenScene::COpenScene()
{
	StageOpenSound = RESOURCE->LoadSound(L"StageopenSound", L"Sound\\WorldSelect.wav");
	open = nullptr;

}

COpenScene::~COpenScene()
{
}

void COpenScene::Init()
{
	
	
}

void COpenScene::Enter()
{
	open = new CSceneOpen();
	open->SetPos(400, 300);
	AddGameObject(open);

	CAMERA->FadeIn(0.25f);
	SOUND->Play(StageOpenSound, 0.1f, true);
}

void COpenScene::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}

}

void COpenScene::Render()
{
}

void COpenScene::Exit()
{
	SOUND->Pause(StageOpenSound);
	DeleteAll();
}

void COpenScene::Release()
{
}
