#include "framework.h"
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
#include "CAnimator.h"
#include "CEventManager.h" 
#include "CRenderManager.h"
#include "CGameObject.h"
#include "CBackGround.h"
#include "CGameManager.h"
#include "CKirbyIcon.h"

CSceneState02::CSceneState02()
{
	pkirby = nullptr;
	bossMonster = nullptr;
	BossBGMSound = RESOURCE->LoadSound(L"BossMapSound", L"Sound\\BossBgm.mp3");
	ClickSound = RESOURCE->LoadSound(L"BossClickSound", L"Sound\\Click.wav");

}

CSceneState02::~CSceneState02()
{
}

void CSceneState02::Init()
{
	
}

void CSceneState02::Enter()
{
	SOUND->Play(BossBGMSound, 0.1f, true);

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

	CImageObject* BossBackGround = new CImageObject;
	BossBackGround->SetImage(RESOURCE->LoadImg(L"BbackGround1", L"Image\\Monster\\King\\BossStage1.png"));
	AddGameObject(BossBackGround);

	bossMonster = new CBossMonster();
	bossMonster->SetPos(700, 450); // 700 450
	AddGameObject(bossMonster);

	CKirbyIcon* icon = new CKirbyIcon;
	icon->SetPos(8, 558);
	icon->SetScale(125, 50);
	AddGameObject(icon);

	CAMERA->SetTargetPos(Vector(432, 400));
	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Stage03.tile");
}

void CSceneState02::Update()
{
	 
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
		SOUND->Play(ClickSound, 0.1f, false);
	}
	
}

void CSceneState02::Render()
{
}

void CSceneState02::Exit()
{
	SOUND->Pause(BossBGMSound);
	DeleteAll();
}

void CSceneState02::Release()
{
}
