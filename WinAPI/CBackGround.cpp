#include "framework.h"
#include "CBackGround.h"

CBackGround::CBackGround()
{
	m_pBossmapImage = nullptr;
	m_pAnimator = nullptr;
}

CBackGround::~CBackGround()
{
}

void CBackGround::Init()
{
	m_pBossmapImage = RESOURCE->LoadImg(L"Background1", L"Image\\Monster\\King\\BossStage.png");
	m_pAnimator		= new CAnimator;

	m_pAnimator->CreateAnimation(L"bossmap", m_pBossmapImage, Vector(0.f, 0.f), Vector(1040.f, 1145.f), Vector(1060.f, 0.f), 0.15f, 12);


	m_pAnimator->Play(L"bossmap", false);
	AddComponent(m_pAnimator);

}

void CBackGround::Update()
{
}

void CBackGround::Render()
{
}

void CBackGround::Release()
{
}

