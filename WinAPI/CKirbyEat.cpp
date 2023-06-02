#include "framework.h"
#include "CKirbyEat.h"
#include "CMonster.h"

CKirbyEat::CKirbyEat()
{
	m_pAnimator = nullptr;
	m_pAttackImage = nullptr;
	m_strName = L"»¡¾ÆµéÀÌ±â";
}

CKirbyEat::~CKirbyEat()
{
}

void CKirbyEat::Init()
{
	m_pAttackImage = RESOURCE->LoadImg(L"KirbyEat", L"Image\\Kirby\\Basic\\KirbyEatEffect.png");
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"AttackR", m_pAttackImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(0.f, 0.f), 0.f, 1);
	m_pAnimator->CreateAnimation(L"AttackL", m_pAttackImage, Vector(0.f, 0.f), Vector(125.f, 101.f), Vector(125.f, 0.f), 0.5f, 2);

	m_pAnimator->Play(L"AttackR", false);
	AddComponent(m_pAnimator);
	
	AddCollider(ColliderType::Rect, Vector(80, 60), Vector(0, 0));
}

void CKirbyEat::Update()
{

}

void CKirbyEat::Render()
{
}

void CKirbyEat::Release()
{
}




