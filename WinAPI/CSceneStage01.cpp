#include "framework.h"
#include "CSceneStage01.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CPathManager.h"
#include "CKirby.h"
#include "CNomalKirby.h"

#include "CMonster.h"
#include "CCameraController.h"
#include "CButton.h"
#include "CPanel.h"
#include "CImageObject.h"
#include "CResourceManager.h"


CSceneStage01::CSceneStage01()
{
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{
	pkirby = new CNomalKirby();
	pkirby->SetPos(200, 300);
	AddGameObject(pkirby);

	CCameraController* pCamController = new CCameraController;
	AddGameObject(pCamController);
	
	CImageObject* pBackGround = new CImageObject();
	pBackGround->SetImage(RESOURCE->LoadImg(L"BackGround", L"Image\\BackGround2.png"));
	pBackGround->SetPos(0, 0);
	AddGameObject(pBackGround);

	CImageObject* pGround = new CImageObject();
	pGround->SetImage(RESOURCE->LoadImg(L"Ground", L"Image\\Ground.png"));
	pGround->SetPos(0, 0);
	AddGameObject(pGround);
	
}

void CSceneStage01::Enter()
{
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
	CAMERA->SetTargetObj(pkirby);
}

void CSceneStage01::Render()
{
}

void CSceneStage01::Exit()
{
}

void CSceneStage01::Release()
{
}
