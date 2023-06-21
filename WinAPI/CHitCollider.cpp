#include "framework.h"
#include "CHitCollider.h"
#include "CMonster.h"
#include "CKirby.h"
#include "CSwordMonster.h"

CHitCollider::CHitCollider()
{
	m_layer = Layer::HitCollider;
	m_strName = L"공격콜라이더";
}

CHitCollider::~CHitCollider()
{
}

void CHitCollider::Init()
{
	AddCollider(ColliderType::Rect, Vector(100, 100), Vector(0, 0));
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
void CHitCollider::SetMonster(CMonster* monster)
{
	this->monster = monster;
}
void CHitCollider::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Player)
	{
		monster->m_vecLookDir = Vector(1, 0);
		// 플레이어가 콜라이더에 부딪히면 부딪히면 몬스터의 시선은 플레이어의 위치를 봐라
	}
}
