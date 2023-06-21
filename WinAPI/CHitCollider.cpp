#include "framework.h"
#include "CHitCollider.h"
#include "CMonster.h"
#include "CKirby.h"
#include "CSwordMonster.h"

CHitCollider::CHitCollider()
{
	m_layer = Layer::HitCollider;
	m_strName = L"�����ݶ��̴�";
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
		// �÷��̾ �ݶ��̴��� �ε����� �ε����� ������ �ü��� �÷��̾��� ��ġ�� ����
	}
}
