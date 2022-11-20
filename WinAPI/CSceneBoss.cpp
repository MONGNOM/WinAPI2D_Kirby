#include "framework.h"
#include "CSceneBoss.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CButton.h"
#include "CPanel.h"
#include "CGround.h"
#include "CBackGround.h"
#include "CLightMonster.h"
#include "CLightKirby.h"
#include "CIceMonster.h"
#include "CKIngMonster.h"


CSceneBoss::CSceneBoss()
{
	pPlayer = nullptr;
	LPlayer = nullptr;
}

CSceneBoss::~CSceneBoss()
{
}

void CSceneBoss::Init()
{
}

void CSceneBoss::Enter()
{


	CKIngMonster* pMonster123 = new CKIngMonster();
	pMonster123->SetPos(700, 300);
	AddGameObject(pMonster123);

	//CGround* Ground = new CGround;
	//Ground->SetImage(RESOURCE->LoadImg(L"BackGround", L"Image\\BossStage1.png"));
	//AddGameObject(Ground);

	CImageObject* BossBackGround = new CImageObject;
	BossBackGround->SetImage(RESOURCE->LoadImg(L"BbackGround1", L"Image\\BossStage123.png"));
	AddGameObject(BossBackGround);

	pPlayer = new CPlayer();
	pPlayer->SetPos(100, 500);
	ADDOBJECT(pPlayer);

	CAMERA->SetTargetPos(Vector(432,332));

	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Boss.tile");

}

void CSceneBoss::Update()
{

	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}
}

void CSceneBoss::Render()
{
}

void CSceneBoss::Exit()
{
	DeleteAll();

}

void CSceneBoss::Release()
{
}
