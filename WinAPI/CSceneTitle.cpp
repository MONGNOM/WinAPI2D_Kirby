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
	open = nullptr;
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

	CImageObject* press = new CImageObject;
	press->SetImage(RESOURCE->LoadImg(L"font", L"Image\\font-2.png"));
	press->SetPos(250, 425);
	AddGameObject(press);


}

void CSceneTitle::Update()
{
	if (BUTTONDOWN(VK_F1))
	{
		CHANGESCENE(GroupScene::TileTool);
	}
	if (BUTTONDOWN('1'))
	{
		CHANGESCENE(GroupScene::Stage01);
	}
	if (BUTTONDOWN(VK_RETURN))
	{
		CAMERA->FadeOut(0.25f);
		SOUND->Play(ClickSound, 0.1f, false);
		DELAYCHANGESCENE(GroupScene::Opne, 0.25f);
	}
}

void CSceneTitle::Render()
{
	
}

void CSceneTitle::Exit()
{
	SOUND->Pause(TitleSound);

}

void CSceneTitle::Release()
{
}
