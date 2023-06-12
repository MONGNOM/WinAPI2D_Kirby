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
#include "CBossMonster.h"

CSceneStage01::CSceneStage01()
{
	pkirby = nullptr;
	icekirby = nullptr;
	pBasicMonster = nullptr;
	swordkirby = nullptr;
	iceMonster = nullptr;
	swordMonster = nullptr;
	bossMonster = nullptr;
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{
}

void CSceneStage01::Enter()
{

	/*pkirby = new CNomalKirby();
	pkirby->SetPos(100, 300);
	AddGameObject(pkirby);*/

	swordkirby = new CSwordKirby();
	swordkirby->SetPos(4930, 300);
	AddGameObject(swordkirby);

	/*icekirby = new CIceKirby();
	icekirby->SetPos(200, 300);
	AddGameObject(icekirby);*/

	/*pBasicMonster = new CBasicMonster();
	pBasicMonster->SetPos(400, 300);
	AddGameObject(pBasicMonster);

	iceMonster = new CIceMonster();
	iceMonster->SetPos(500, 300);
	AddGameObject(iceMonster);*/

	CDoor* door = new CDoor();
	door->SetPos(4830, 350);
	AddGameObject(door);


	swordMonster = new CSwordMonster();
	swordMonster->SetPos(500, 300);
	AddGameObject(swordMonster);

	bossMonster = new CBossMonster();
	bossMonster->SetPos(200, 300);
	//AddGameObject(bossMonster);

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

	CAMERA->SetTargetObj(swordkirby);
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
