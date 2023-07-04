#include "framework.h"
#include "CIceAttack.h"
#include "CGameManager.h"

CIceAttack::CIceAttack()
{
	m_pAnimator = nullptr;
	m_pAttackImage = nullptr;
	m_strName = L"¾ó¸®±â";
	damage = 1;
}

CIceAttack::~CIceAttack()
{

}

void CIceAttack::Init()
{
	m_pAttackImage = RESOURCE->LoadImg(L"IceAttackKirby", L"Image\\Effect.png");
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"AttackL", m_pAttackImage, Vector(0.f, 800.f), Vector(220.f, 100.f), Vector(230.f, 0.f), 0.03f, 12);
	m_pAnimator->CreateAnimation(L"AttackR", m_pAttackImage, Vector(2550.f, 800.f), Vector(220.f, 100.f), Vector(-230.f, 0.f), 0.03f, 12);

	m_pAnimator->Play(L"AttackR", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(140, 80), Vector(0, 0));
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

void CIceAttack::Attack()
{
	if (kirby->m_vecLookDir.x == -1)
	{
		iceAttackstate = L"AttackL";

	}
	if (kirby->m_vecLookDir.x == 1)
	{
		iceAttackstate = L"AttackR";
	}
	AnimatorUpdate();
}

void CIceAttack::AnimatorUpdate()
{
	m_pAnimator->Play(iceAttackstate, false);
}
