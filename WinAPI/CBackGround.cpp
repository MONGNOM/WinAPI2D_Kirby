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
	m_vecPos = Vector(CAMERA->GetLookAt().x , CAMERA->GetLookAt().y);
}

void CBackGround::Render()
{
	
	RENDER->Image(m_pStage1BackGroundImage, CAMERA->GetLookAt().x * 0.8f - 400, CAMERA->GetLookAt().y * 0.8f - 300, CAMERA->GetLookAt().x * 0.8f + 1024 , CAMERA->GetLookAt().y * 0.8f + 320);
}

void CBackGround::Release()
{
}

