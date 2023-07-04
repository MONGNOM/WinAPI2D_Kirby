#include "framework.h"
#include "CEffect.h"

CEffect::CEffect()
{
	 m_pAnimator = nullptr;
	 Effect = nullptr;
	 m_layer = Layer::Effect;
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

//void CEffect::NomalAttackDestoryEffect()
//{
//	Effectstate = L"NomalAttackDestoryEffect";
//}
//
//void CEffect::MonsterIceDeathEffect()
//{
//	Effectstate = L"MonsterIceDeathEffect";
//}
//
//void CEffect::KirbyDashEffectL()
//{
//	Effectstate = L"KirbyDashEffectL";
//
//}
//
//void CEffect::KirbyDashEffectR()
//{
//	Effectstate = L"KirbyDashEffectR";
//}

void CEffect::Init()
{
	Effect = RESOURCE->LoadImg(L"Effect", L"Image\\Effect.png");
	
	m_pAnimator = new CAnimator();
	m_pAnimator->CreateAnimation(L"MonsterDeathEffect", Effect, Vector(0.f, 120.f), Vector(170.f, 170.f), Vector(162.f, 0.f), 0.03f, 14, false);
	m_pAnimator->CreateAnimation(L"kirbyChangeEffect", Effect, Vector(0.f, 290.f), Vector(170.f, 170.f), Vector(175.f, 0.f), 0.03f, 11, false);
	/*m_pAnimator->CreateAnimation(L"NomalAttackDestoryEffect", Effect, Vector(0.f, 800.f), Vector(220.f, 100.f), Vector(230.f, 0.f), 0.03f, 12);
	m_pAnimator->CreateAnimation(L"MonsterIceDeathEffect", Effect, Vector(0.f, 800.f), Vector(220.f, 100.f), Vector(230.f, 0.f), 0.03f, 12);
	m_pAnimator->CreateAnimation(L"KirbyDashEffectL", Effect, Vector(0.f, 800.f), Vector(220.f, 100.f), Vector(230.f, 0.f), 0.03f, 12);
	m_pAnimator->CreateAnimation(L"KirbyDashEffectR", Effect, Vector(0.f, 800.f), Vector(220.f, 100.f), Vector(230.f, 0.f), 0.03f, 12);*/

	AddComponent(m_pAnimator);
}

void CEffect::Update()
{
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
