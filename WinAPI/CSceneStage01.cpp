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

CSceneStage01::CSceneStage01()
{
	pPlayer = nullptr;
	LPlayer = nullptr;
	m_LightChange = false;
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

	CMonster* pMonster = new CMonster();
	pMonster->SetPos(700, 300);
	AddGameObject(pMonster);

	CLightMonster* pMonster1 = new CLightMonster();
	pMonster1->SetPos(450, 300);
	AddGameObject(pMonster1);

	CCameraController* pCamController = new CCameraController;
	AddGameObject(pCamController);

	CGround* Ground = new CGround;
	Ground->SetImage(RESOURCE->LoadImg(L"BackGround", L"Image\\Ground.png"));
	AddGameObject(Ground);

	CBackGround* BackGround = new CBackGround;
	BackGround->SetImage(RESOURCE->LoadImg(L"BbackGround", L"Image\\BackGround_1.png"));
	AddGameObject(BackGround);

	pPlayer = new CPlayer();
	pPlayer->SetPos(250, 500);
	ADDOBJECT(pPlayer);
	
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
