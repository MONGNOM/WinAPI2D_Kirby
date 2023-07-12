#include "framework.h"
#include "CSceneTitle.h"

#include "WinAPI.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CImageObject.h"

CSceneTitle::CSceneTitle()
{
	ClickSound = RESOURCE->LoadSound(L"ClickSound", L"Sound\\Click.wav");
	TitleSound = RESOURCE->LoadSound(L"TitleSound", L"Sound\\KirbyMainBgm.mp3");
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Init()
{
}

void CSceneTitle::Enter()
{
	SOUND->Play(TitleSound, 0.1f, true);
	CAMERA->FadeIn(0.25f);

	CImageObject* Title = new CImageObject;
	Title->SetImage(RESOURCE->LoadImg(L"Title", L"Image\\Title.bmp"));
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
		SOUND->Play(ClickSound, 0.1f, false);
		DELAYCHANGESCENE(GroupScene::Stage01, 0.25f);
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
	SOUND->Pause(TitleSound);

}

void CSceneTitle::Release()
{
}
