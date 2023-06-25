#include "framework.h"
#include "CHitCollider.h"
#include "CMonster.h"
#include "CKirby.h"
#include "CSwordMonster.h"
#include "CIceMonster.h"

CHitCollider::CHitCollider()
{
	m_layer = Layer::HitCollider;
	m_strName = L"공격콜라이더";
	colliderx = 50;
	collidery = 50;

}

CHitCollider::~CHitCollider()
{
}

void CHitCollider::Init()
{
	AddCollider(ColliderType::Rect, Vector(colliderx, collidery), Vector(0, 0));
}

void CHitCollider::Update()
{
}

void CHitCollider::Render()
{
}

void CHitCollider::Release()
{
}
void CHitCollider::SetColliderScale(float x, float y)
{
	colliderx = x;
	collidery = y;
}
void CHitCollider::SetMonster(CMonster* monster)
{
	this->monster = monster;
}



void CHitCollider::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Player)
	{
		// 플레이어쪽 방향으로 시선돌리기
		if (monster->GetPos().x > pOtherCollider->GetOwner()->GetPos().x)
		monster->m_vecLookDir = Vector(-1,0);
		else
		monster->m_vecLookDir = Vector(1, 0);
		// 플레이어가 닿으면 상태가 어택으로 되어야함  [조건] 
		
		//attackMonser-> m_state = CIceMonster::State::Attack; 로 하면 아이스몬스터는 바뀌는데 다른몬스터 콜라이더랑 부딪히면 오류남
		
	}
}
