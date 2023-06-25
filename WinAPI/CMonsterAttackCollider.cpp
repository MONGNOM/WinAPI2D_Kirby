#include "framework.h"
#include "CMonsterAttackCollider.h"

CMonsterAttackCollider::CMonsterAttackCollider()
{
	m_layer = Layer::HitCollider;
	colliderx = 50;
	collidery = 50;
	icemonster = nullptr;
	swordmonster = nullptr;
}

CMonsterAttackCollider::~CMonsterAttackCollider()
{
}


void CMonsterAttackCollider::Init()
{
	AddCollider(ColliderType::Rect, Vector(colliderx, collidery), Vector(0, 0));
}

void CMonsterAttackCollider::Update()
{
}

void CMonsterAttackCollider::Render()
{
}

void CMonsterAttackCollider::Release()
{
}

void CMonsterAttackCollider::SetColliderScale(float x, float y)
{
	colliderx = x;
	collidery = y;
}

void CMonsterAttackCollider::SetIceMonster(CIceMonster* ice)
{
	this->icemonster = ice;
}

void CMonsterAttackCollider::SetSwordMonster(CSwordMonster* sword)
{
	this->swordmonster = sword;
}

void CMonsterAttackCollider::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Player)
	{
		if (icemonster)
		icemonster->m_state = CIceMonster::State::Attack;
		else if(swordmonster)
		swordmonster->m_state = CSwordMonster::State::Attack;
	}
}
