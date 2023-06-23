#include "framework.h"
#include "CMonsterIceAttack.h"

CMonsterIceAttack::CMonsterIceAttack()
{
	m_pAnimator = nullptr;
	m_pAttackImage = nullptr;
}

CMonsterIceAttack::~CMonsterIceAttack()
{

}

void CMonsterIceAttack::Init()
{
	m_pAttackImage = RESOURCE->LoadImg(L"MonstericeATtack", L"Image\\Monster\\IceMonster\\IceMonsterAttack.png");
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"AttackR", m_pAttackImage, Vector(0.f, 0.f), Vector(70.f, 75.f), Vector(100.f, 0.f), 0.03f, 4);
	//m_pAnimator->CreateAnimation(L"AttackL", m_pAttackImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(125.f, 0.f), 0.03f, 7);

	m_pAnimator->Play(L"AttackR", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(80, 60), Vector(0, 0));
}

void CMonsterIceAttack::Update()
{

}

void CMonsterIceAttack::Render()
{
}

void CMonsterIceAttack::Release()
{
}
