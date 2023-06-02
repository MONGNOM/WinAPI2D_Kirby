#include "framework.h"
#include "CImageObject.h"
#include "CBonusMap.h"


CBonusMap::CBonusMap()
{
	pPersimon = nullptr;
}

CBonusMap::~CBonusMap()
{
}

void CBonusMap::Init()
{
}

void CBonusMap::Enter()
{
	CImageObject* Bonus = new CImageObject;
	Bonus->SetImage(RESOURCE->LoadImg(L"BounsMap", L"Image\\Bonus2.png"));
	AddGameObject(Bonus);

	pPersimon = new CPersimmon();
	pPersimon->GetPos();
	AddGameObject(pPersimon);


	CAMERA->SetTargetPos(Vector(432, 300));
	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Stage03.tile");
}

void CBonusMap::Update()
{
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
}

void CBonusMap::Release()
{
}
