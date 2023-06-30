#include "framework.h"
#include "CSceneStage01.h"
#include "CSceneState02.h"

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
#include "CGameManager.h"
#include "CKirbyIcon.h"

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

	pkirby = new CNomalKirby();
	pkirby->SetPos(100, 300);
	AddGameObject(pkirby);

	pBasicMonster = new CBasicMonster();
	pBasicMonster->SetPos(400, 300);
	AddGameObject(pBasicMonster);

	iceMonster = new CIceMonster();
	iceMonster->SetPos(500, 300);
	AddGameObject(iceMonster);

	CDoor* door = new CDoor();
	door->SetPos(4830, 350);
	AddGameObject(door);


	swordMonster = new CSwordMonster();
	swordMonster->SetPos(800, 200);
	AddGameObject(swordMonster);

	CCameraController* pCamController = new CCameraController;
	AddGameObject(pCamController);

	CKirbyIcon* icon = new CKirbyIcon;
	icon->SetPos(8, 558);
	icon->SetScale(125, 50);
	AddGameObject(icon);

	CImageObject* pBackGround = new CImageObject();
	pBackGround->SetImage(RESOURCE->LoadImg(L"BackGround", L"Image\\map12.png"));
	pBackGround->SetPos(0, 0);
	AddGameObject(pBackGround);

	CImageObject* pGround = new CImageObject();
	pGround->SetImage(RESOURCE->LoadImg(L"Ground", L"Image\\Ground12.png"));
	pGround->SetPos(0, 0);
	AddGameObject(pGround);

	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Stage01.tile");
}

void CSceneStage01::Update()
{
	if (GAME->playerPos.x >= 4658)
	{
		CAMERA->SetTargetPos(Vector(4658, GAME->playerPos.y), 0.1f);
	}
	else if (GAME->playerPos.x <= 400)
	{
		CAMERA->SetTargetPos(Vector(400, GAME->playerPos.y), 0.1f);
	}
	else
		CAMERA->SetTargetPos(GAME->playerPos, 0.1f);

	if (GAME->playerPos.y >= 300 || GAME->playerPos.y <= 300)
	{
		CAMERA->SetTargetPos(Vector(GAME->playerPos.x, 300));
	}

	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}

	if (BUTTONDOWN(VK_SPACE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Bonus, 0.25f);
	}

	if (BUTTONDOWN('1'))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Stage02, 0.25f);
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
