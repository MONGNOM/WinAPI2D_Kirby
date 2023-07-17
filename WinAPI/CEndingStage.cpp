#include "framework.h"
#include "CEndingStage.h"

CEndingStage::CEndingStage()
{
	endSound = RESOURCE->LoadSound(L"endSound", L"Sound\\Ending.wav");
	end = nullptr;

}

CEndingStage::~CEndingStage()
{
}

void CEndingStage::Init()
{
}

void CEndingStage::Enter()
{
	end = new EndingScene();
	end->SetPos(400, 300);
	AddGameObject(end);

	CAMERA->FadeIn(0.25f);
	SOUND->Play(endSound, 0.1f, true);
}

void CEndingStage::Update()
{
	
}

void CEndingStage::Render()
{
}

void CEndingStage::Exit()
{
	SOUND->Pause(endSound);
	DeleteAll();
}

void CEndingStage::Release()
{
}
