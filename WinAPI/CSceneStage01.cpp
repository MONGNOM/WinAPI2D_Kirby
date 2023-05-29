#include "framework.h"
#include "CSceneStage01.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CPathManager.h"
#include "CNomalKirby.h"
#include "CIceKirby.h"
#include "CSwordKirby.h"


#include "CMonster.h"
#include "CCameraController.h"
#include "CButton.h"
#include "CPanel.h"
#include "CImageObject.h"
#include "CResourceManager.h"


CSceneStage01::CSceneStage01()
{
	pkirby = nullptr;
	icekirby = nullptr;
	pBasicMonster = nullptr;
	swordkirby = nullptr;
	iceMonster = nullptr;
	swordMonster = nullptr;
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{
	pkirby = new CNomalKirby();
	pkirby->SetPos(100, 300);
	AddGameObject(pkirby);

	/*icekirby = new CIceKirby();
	icekirby->SetPos(200, 300);
	AddGameObject(icekirby);*/

	swordkirby = new CSwordKirby();
	swordkirby->SetPos(300, 300);
	AddGameObject(swordkirby);

	pBasicMonster = new CBasicMonster();
	pBasicMonster->SetPos(400, 300);
	AddGameObject(pBasicMonster);

	iceMonster = new CIceMonster();
	iceMonster->SetPos(500, 300);
	AddGameObject(iceMonster);

	swordMonster = new CSwordMonster();
	swordMonster->SetPos(600, 300);
	AddGameObject(swordMonster);
	

	CCameraController* pCamController = new CCameraController;
	AddGameObject(pCamController);
	
	/*CImageObject* pBackGround = new CImageObject();
	pBackGround->SetImage(RESOURCE->LoadImg(L"BackGround", L"Image\\BackGround2.png"));
	pBackGround->SetPos(0, 0);
	AddGameObject(pBackGround);*/

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
	CAMERA->SetTargetObj(swordkirby);
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
