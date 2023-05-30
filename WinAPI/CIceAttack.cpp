#include "framework.h"
#include "CIceAttack.h"

CIceAttack::CIceAttack()
{
	m_pAnimator = nullptr;
	m_pAttackImage = nullptr;
	//m_strName = L"¾ó¸®±â";
	damage = 1;

}

CIceAttack::~CIceAttack()
{

}

void CIceAttack::Init()
{
	m_pAttackImage = RESOURCE->LoadImg(L"KirbyAttackIce", L"Image\\Kirby\\Ice\\IceKirbyAttackEffect.png");
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"AttackR", m_pAttackImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.03f, 7);
	m_pAnimator->CreateAnimation(L"AttackL", m_pAttackImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(125.f, 0.f), 0.03f, 7);

	m_pAnimator->Play(L"AttackR", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(80, 60), Vector(0, 0));
}

void CIceAttack::Update()
{

}

void CIceAttack::Render()
{
}

void CIceAttack::Release()
{
}
