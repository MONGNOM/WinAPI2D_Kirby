#include "framework.h"
#include "CSceneStage01.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CPathManager.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CCameraController.h"
#include "CButton.h"
#include "CPanel.h"
#include "CImageObject.h"

CSceneStage01::CSceneStage01()
{
	pPlayer = nullptr;

}

CSceneStage01::~CSceneStage01()
{
}



void CSceneStage01::Init()
{
	
}

void CSceneStage01::Enter()
{
	pPlayer = new CPlayer();
	pPlayer->SetPos(WINSIZEX * 0.5f, 750);
	AddGameObject(pPlayer);

	CMonster* pMonster = new CMonster();
	pMonster->SetPos(800, WINSIZEY * 0.5f);
	AddGameObject(pMonster);

	CCameraController* pCamController = new CCameraController;
	AddGameObject(pCamController);

	CImageObject* BackGround = new CImageObject;
	BackGround->SetImage(RESOURCE->LoadImg(L"BackGround", L"Image\\123.png"));
	AddGameObject(BackGround);

	CImageObject* BBackGround = new CImageObject;
	BBackGround->SetImage(RESOURCE->LoadImg(L"BackGround", L"Image\\BB123.png"));
	AddGameObject(BBackGround);
	CAMERA->SetTargetObj(pPlayer);
	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Stage01.tile");

}

void CSceneStage01::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}
	

}

void CSceneStage01::Render()
{
	
}

void CSceneStage01::Exit()
{
	DeleteAll();
}

void CSceneStage01::Release()
{
}
