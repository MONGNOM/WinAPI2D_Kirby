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
#include "CKirbyHp.h"
#include "CKirbyStatus.h"


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
	CKirbyHp* HP = new CKirbyHp;
	HP->SetPos(110, 550);
	HP->SetScale(270, 50);
	ADDOBJECT(HP);

	CKIngMonster* pMonster123 = new CKIngMonster();
	pMonster123->SetPos(700, 300);
	AddGameObject(pMonster123);

	CImageObject* BossBackGround = new CImageObject;
	BossBackGround->SetImage(RESOURCE->LoadImg(L"BbackGround1", L"Image\\BossStage12345.png"));
	AddGameObject(BossBackGround);

	pPlayer = new CPlayer();
	pPlayer->SetPos(100, 500);
	ADDOBJECT(pPlayer);

	CKirbyStatus* status = new CKirbyStatus;
	status->SetPos(8, 558);
	status->SetScale(125, 50);
	AddGameObject(status);

	CAMERA->SetTargetPos(Vector(430,400));

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
