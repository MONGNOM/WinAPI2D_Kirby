#include "framework.h"

#include "CImageObject.h"

#include "CBonusMap.h"

#include "CBossDoor.h"
#include "CResourceManager.h"
#include "WinAPI.h"
#include "CRenderManager.h"
#include "CImageObject.h"
#include "CMeat.h"
#include "CIceItem.h"
#include "CSwordItem.h"
#include "CNomalKirby.h"
#include "CGameManager.h"
#include "CIceKirby.h"
#include "CSwordKirby.h"


CBonusMap::CBonusMap()
{
	pPersimon = nullptr;
	pkirby = nullptr;
}

CBonusMap::~CBonusMap()
{
}

void CBonusMap::Init()
{
}

void CBonusMap::Enter()
{
	if (GAME->ice)
	{
		CIceKirby* icekirby = new CIceKirby();
		icekirby->SetPos(100, 500);
		AddGameObject(icekirby);
	}
	else if (GAME->sword)
	{
		CSwordKirby* swordkirby = new CSwordKirby();
		swordkirby->SetPos(100, 500);
		AddGameObject(swordkirby);
	}
	else
	{
		pkirby = new CNomalKirby();
		pkirby->SetPos(100, 500);
		AddGameObject(pkirby);
	}

	CImageObject* Bonus = new CImageObject;
	Bonus->SetImage(RESOURCE->LoadImg(L"BounsMap", L"Image\\Bonus3.png"));
	AddGameObject(Bonus);

	pPersimon = new CPersimmon();
	pPersimon->SetPos(635, 470);
	AddGameObject(pPersimon);

	CIceItem* iceitem = new CIceItem();
	iceitem->SetPos(120, 250);
	AddGameObject(iceitem);

	CSwordItem* sworditem = new CSwordItem();
	sworditem->SetPos(720, 250);
	AddGameObject(sworditem);

	CMeat* meat = new CMeat();
	meat->SetPos(200, 470);
	AddGameObject(meat);

	CBossDoor* door = new CBossDoor();
	door->SetPos(435, 425);
	AddGameObject(door);

	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Stage03.tile");
}

void CBonusMap::Update()
{

	CAMERA->SetTargetPos(Vector(432, 300));

	if (BUTTONDOWN(VK_SPACE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Stage02, 0.25f);
	}
}

void CBonusMap::Render()
{
}

void CBonusMap::Exit()
{
	DeleteAll();
}

void CBonusMap::Release()
{
}
