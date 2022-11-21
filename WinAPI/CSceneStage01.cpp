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
#include "CGround.h"
#include "CBackGround.h"
#include "CLightMonster.h"
#include "CLightKirby.h"
#include "CIceMonster.h"
#include "CKIngMonster.h"
#include "CDoor.h"
#include "CKirbyHp.h"
#include "CKirbyStatus.h"

CSceneStage01::CSceneStage01()
{
	pPlayer = nullptr;
	LPlayer = nullptr;
	m_Basic = true;

}

CSceneStage01::~CSceneStage01()
{
}



void CSceneStage01::Init()
{
	
}

void CSceneStage01::Enter()
{

	


	CMonster* pMonster1 = new CMonster();
	pMonster1->SetPos(1500, 200);
	AddGameObject(pMonster1);

	CLightMonster* pMonster134 = new CLightMonster();
	pMonster134->SetPos(4400, 200);
	AddGameObject(pMonster134);

	CIceMonster* pMonster12 = new CIceMonster();
	pMonster12->SetPos(3500, 200);
	AddGameObject(pMonster12);

	CDoor* Door = new CDoor();
	Door->SetPos(4930, 440);
	AddGameObject(Door);

	CKirbyHp* HP = new CKirbyHp;
	HP->SetPos(110,550);
	HP->SetScale(270,50);
	AddGameObject(HP);

	CKirbyStatus* status = new CKirbyStatus;
	status->SetPos(8, 558);
	status->SetScale(125, 50);
	AddGameObject(status);

	
	CCameraController* pCamController = new CCameraController;
	AddGameObject(pCamController);

	CGround* Ground = new CGround;
	Ground->SetImage(RESOURCE->LoadImg(L"BackGround", L"Image\\Ground.png"));
	AddGameObject(Ground);

	CBackGround* BackGround = new CBackGround;
	BackGround->SetImage(RESOURCE->LoadImg(L"BbackGround", L"Image\\BackGround_1.png"));
	AddGameObject(BackGround);

	pPlayer = new CPlayer();
	pPlayer->SetPos(230, 500);  // 230 500
	ADDOBJECT(pPlayer);

	CAMERA->SetTargetPos(Vector(400, 500));
	

	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Stage01.tile");


}

void CSceneStage01::Update()
{

	if (GAME->PlayerPos.x >= 4658)
	{
		CAMERA->SetTargetPos(Vector(4658, GAME->PlayerPos.y),0.1f);
	}
	else if (GAME->PlayerPos.x <= 400)
	{
		CAMERA->SetTargetPos(Vector(400, GAME->PlayerPos.y),0.1f);

	}
	else
		CAMERA->SetTargetPos(GAME->PlayerPos,0.1f);


	


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
