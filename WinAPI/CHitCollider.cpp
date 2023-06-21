#include "framework.h"
#include "CHitCollider.h"
#include "CMonster.h"
#include "CKirby.h"
#include "CSwordMonster.h"

CHitCollider::CHitCollider()
{
	m_layer = Layer::HitCollider;
	m_strName = L"�����ݶ��̴�";
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
		if (monster->GetPos().x > pOtherCollider->GetOwner()->GetPos().x)
		monster->m_vecLookDir = Vector(-1,0);
		else
		monster->m_vecLookDir = Vector(1, 0);
		// �÷��̾ �ݶ��̴��� �ε����� �ε����� ������ �ü��� �÷��̾��� ��ġ�� ����
	}
}
