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






CSceneState02::CSceneState02()
{
	bossMonster = nullptr;
}

CSceneState02::~CSceneState02()
{
}

void CSceneState02::Init()
{
	
}

void CSceneState02::Enter()
{
	//CBackGround* pback = new CBackGround();
	//pback->SetPos(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
	//AddGameObject(pback);

	CImageObject* BossBackGround = new CImageObject;
	BossBackGround->SetImage(RESOURCE->LoadImg(L"BbackGround1", L"Image\\Monster\\King\\BossStage1.png"));
	AddGameObject(BossBackGround);

	CAMERA->SetTargetPos(Vector(432, 400));
	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Stage02.tile");
}

void CSceneState02::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}
	
}

void CSceneState02::Render()
{
}

void CSceneState02::Exit()
{
	DeleteAll();
}

void CSceneState02::Release()
{
}
