#include "framework.h"
#include "CSceneTitle.h"

#include "WinAPI.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"

CSceneTitle::CSceneTitle()
{
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Init()
{
}

void CSceneTitle::Enter()
{
	CAMERA->FadeIn(0.25f);

	BackGroundSound1 = RESOURCE->LoadSound(L"KirbyMainBgm", L"Sound\\KirbyMainBgm.mp3");
	SOUND->Play(BackGroundSound1, 0.1f, true);


	CImageObject* Title = new CImageObject;
	Title->SetImage(RESOURCE->LoadImg(L"Title", L"Image\\Title.png"));
	AddGameObject(Title);
}

void CSceneTitle::Update()
{
	if (BUTTONDOWN(VK_F1))
	{
		CHANGESCENE(GroupScene::TileTool);
	}
	if (BUTTONDOWN(VK_SPACE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Stage01, 0.25f);

		BackGroundSound12 = RESOURCE->LoadSound(L"Click", L"Sound\\Click.wav");
		SOUND->Play(BackGroundSound12, 0.1f, true);
	}
}

void CSceneTitle::Render()
{
	RENDER->Text(L"press space to start",
		WINSIZEX * 0.5f - 100,
		WINSIZEY * 0.5f - 10,
		WINSIZEX * 0.5f + 100,
		WINSIZEY * 0.5f + 295,
		Color(0, 0, 0, 1.f),
		20.f);
}

void CSceneTitle::Exit()
{
	SOUND->Pause(BackGroundSound1); 
	SOUND->Pause(BackGroundSound12);

}

void CSceneTitle::Release()
{
}
