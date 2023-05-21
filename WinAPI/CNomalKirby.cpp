#include "framework.h"
#include "CNomalKirby.h"

CNomalKirby::CNomalKirby()
{
	m_pIdleLImage = nullptr;
	m_pIdleRImage = nullptr;
	m_pMoveLImage = nullptr;
	m_pMoveRImage = nullptr;
	m_pRunImage = nullptr;
	m_pDownImage = nullptr;
	m_pFlyImage = nullptr;
	m_pFlyingImage = nullptr;
	m_pJumpImage = nullptr;
	m_pJumpingImage = nullptr;
	m_pAttackImage = nullptr;

}

CNomalKirby::~CNomalKirby()
{
}


void CNomalKirby::Init()
{
	m_pIdleLImage = RESOURCE->LoadImg(L"KirbyIdleL", L"Image\\Kirby\\Basic\\KirbyIdleL.png");
	m_pIdleRImage = RESOURCE->LoadImg(L"KirbyIdleR", L"Image\\Kirby\\Basic\\KirbyIdleR.png");
	m_pMoveLImage = RESOURCE->LoadImg(L"KirbyLW", L"Image\\Kirby\\Basic\\KirbyLW.png");
	m_pMoveRImage = RESOURCE->LoadImg(L"KirbyRW", L"Image\\Kirby\\Basic\\KirbyRW.png");
	m_pRunImage = RESOURCE->LoadImg(L"KirbyRun", L"Image\\Kirby\\Basic\\KirbyRun.png");
	m_pDownImage = RESOURCE->LoadImg(L"KirbyDown", L"Image\\Kirby\\Basic\\KirbyDown.png");
	m_pFlyImage = RESOURCE->LoadImg(L"KirbyFly", L"Image\\Kirby\\Basic\\KirbyFly.png");
	m_pFlyingImage = RESOURCE->LoadImg(L"KirbyFly", L"Image\\Kirby\\Basic\\KirbyFly.png");
	m_pJumpImage = RESOURCE->LoadImg(L"KirbyJump", L"Image\\Kirby\\Basic\\KirbyJump.png");
	m_pAttackImage = RESOURCE->LoadImg(L"KirbyAttack", L"Image\\Kirby\\Basic\\KirbyEat.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IdleR", m_pIdleRImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"IdleL", m_pIdleLImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"LW", m_pMoveLImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"RW", m_pMoveRImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"RRun", m_pRunImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"LRun", m_pRunImage, Vector(490.f, 104.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"LDown", m_pDownImage, Vector(0.f, 100.f), Vector(50.f, 50.f), Vector(50.f, 0.f), 10.0f, 1);
	m_pAnimator->CreateAnimation(L"RDown", m_pDownImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(50.f, 0.f), 10.0f, 1);
	m_pAnimator->CreateAnimation(L"RFly", m_pFlyImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 19, false);
	m_pAnimator->CreateAnimation(L"RFlying", m_pFlyImage, Vector(400.f, 0.f), Vector(85.f, 50.f), Vector(70.f, 0.f), 0.08f, 6);
	m_pAnimator->CreateAnimation(L"LFly", m_pFlyImage, Vector(0.f, 100.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 19, false);
	m_pAnimator->CreateAnimation(L"LFlying", m_pFlyImage, Vector(400.f, 100.f), Vector(85.f, 50.f), Vector(70.f, 0.f), 0.08f, 6);
	m_pAnimator->CreateAnimation(L"RJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.06f, 9, false);
	m_pAnimator->CreateAnimation(L"LJump", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.06f, 9, false);
	m_pAnimator->CreateAnimation(L"RJumping", m_pJumpImage, Vector(400.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 2);
	m_pAnimator->CreateAnimation(L"LJumping", m_pJumpImage, Vector(400.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 2);
	m_pAnimator->CreateAnimation(L"RAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(57.f, 57.f), Vector(70.f, 0.f), 0.08f, 5);
	m_pAnimator->CreateAnimation(L"LAttack", m_pAttackImage, Vector(0.f, 95.f), Vector(57.f, 57.f), Vector(70.f, 0.f), 0.08f, 5);

	m_pAnimator->Play(L"IdleR", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Circle, Vector(20, 20), Vector(0, 0));
}

void CNomalKirby::Update()
{
}

void CNomalKirby::Render()
{
}

void CNomalKirby::Release()
{
}

void CNomalKirby::Attack()
{
	
}

void CNomalKirby::AnimatorUpdate()
{
}