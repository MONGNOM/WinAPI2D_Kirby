#include "framework.h"
#include "CEffect.h"

CEffect::CEffect()
{
	 m_pAnimator = nullptr;
	 Effect = nullptr;
	 m_layer = Layer::Effect;
	 effectDestory = false;
	 effectDestoryTime = 0;
	 BossEffect = nullptr;
	 dropStarEffect = nullptr;
}

CEffect::~CEffect()
{
}

void CEffect::MonsterDeathEffect()
{

	Effectstate = L"MonsterDeathEffect";
	
}

void CEffect::kirbyChangeEffect()
{
	Effectstate = L"kirbyChangeEffect";
}

void CEffect::NomalAttackDestoryEffect()
{
	Effectstate = L"NomalAttackDestoryEffect";
}



//void CEffect::MonsterIceDeathEffect()
//{
//	Effectstate = L"MonsterIceDeathEffect";
//}

void CEffect::KirbyDashEffectL()
{
	Effectstate = L"KirbyDashEffectL";

}

void CEffect::KirbyDashEffectR()
{
	Effectstate = L"KirbyDashEffectR";

}

void CEffect::BossAttackEffect()
{	
	Effectstate = L"BossAttackEffect";
}

void CEffect::DropStarEffect()
{
	Effectstate = L"dropStarEffect";
}

void CEffect::Init()
{
	dropStarEffect = RESOURCE->LoadImg(L"DropStarEffect", L"Image\\DropStar.png");
	Effect = RESOURCE->LoadImg(L"Effect", L"Image\\Effect.png");
	BossEffect = RESOURCE->LoadImg(L"BossEffect", L"Image\\Effect1.png");
	
	m_pAnimator = new CAnimator();
	m_pAnimator->CreateAnimation(L"MonsterDeathEffect", Effect, Vector(0.f, 120.f), Vector(170.f, 170.f), Vector(162.f, 0.f), 0.03f, 14, false);
	m_pAnimator->CreateAnimation(L"kirbyChangeEffect", Effect, Vector(0.f, 290.f), Vector(170.f, 170.f), Vector(175.f, 0.f), 0.03f, 11, false);
	m_pAnimator->CreateAnimation(L"NomalAttackDestoryEffect", Effect, Vector(0.f, 450.f), Vector(90.f, 110.f), Vector(90.f, 0.f), 0.03f, 9, false);
	//m_pAnimator->CreateAnimation(L"MonsterIceDeathEffect", Effect, Vector(0.f, 800.f), Vector(220.f, 100.f), Vector(230.f, 0.f), 0.03f, 12);
	m_pAnimator->CreateAnimation(L"KirbyDashEffectR", Effect, Vector(0.f, 725.f), Vector(70.f, 30.f), Vector(72.f, 0.f), 0.03f, 19);
	m_pAnimator->CreateAnimation(L"KirbyDashEffectL", Effect, Vector(1281.f, 760.f), Vector(70.f, 30.f), Vector(-72.f, 0.f), 0.03f, 19);

	m_pAnimator->CreateAnimation(L"BossAttackEffect", BossEffect, Vector(0.f, 0.f), Vector(24.f, 25.f), Vector(24.f, 0.f), 0.03f, 4);
	m_pAnimator->CreateAnimation(L"dropStarEffect", dropStarEffect, Vector(0.f, 0.f), Vector(150.f, 150.f), Vector(150.f, 0.f), 0.09f, 3,false);

	AddComponent(m_pAnimator);
}

void CEffect::Update()
{

	if (effectDestory)
	{
		effectDestoryTime += DT;
		if (effectDestoryTime > 0.27f)
		{
			DELETEOBJECT(this);
		}
	}
	AnimatorUpdate();
}

void CEffect::Render()
{
}

void CEffect::Release()
{
}

void CEffect::AnimatorUpdate()
{
	m_pAnimator->Play(Effectstate, false);
}
