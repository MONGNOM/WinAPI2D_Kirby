#include "framework.h"
#include "CBackGround.h"

CBackGround::CBackGround()
{
	m_pStage1BackGroundImage = nullptr;
	m_vecPos = Vector(0, 0);
}

CBackGround::~CBackGround()
{
}

void CBackGround::Init()
{
	m_pStage1BackGroundImage = RESOURCE->LoadImg(L"BackGround", L"Image\\map12.png");
	
}

void CBackGround::Update()
{
	m_vecPos = Vector(CAMERA->GetTargetPos().x  , CAMERA->GetTargetPos().y);
	//여기서 스크롤링을 만등러주면 되겠구먼
}

void CBackGround::Render()
{
	RENDER->Image(m_pStage1BackGroundImage, CAMERA->GetTargetPos().x - 400, CAMERA->GetTargetPos().y - 300, CAMERA->GetTargetPos().x + 1024 , CAMERA->GetTargetPos().y+ 320);
}

void CBackGround::Release()
{
}

