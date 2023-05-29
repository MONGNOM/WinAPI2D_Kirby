#include "framework.h"
#include "CMonster.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CKirbyWeapon.h"

CMonster::CMonster()
{
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Monster;
	m_fSpeed = 0.f;
	m_vecLookDir = Vector(1, 0);
	m_groundchecker = false;
	m_groundCounter = 0;
	m_gravity = 300;
	dieTime = 0;
	hp = 10;
	dizzy = false;
	m_pWeapon = nullptr;

}

CMonster::~CMonster()
{
}

void CMonster::Init()
{
	AddCollider(ColliderType::Rect, Vector(50, 50), Vector(0, 0));
}

void CMonster::Update()
{
	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * DT;
	}
}

void CMonster::Render()
{
	
}

void CMonster::Release()
{
}

void CMonster::TakeDamage(int damage)
{
	hp -= damage;
	dizzy = true;
}

void CMonster::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�ٴ�")
	{
		m_groundCounter++;
		m_groundchecker = true;
	}

	if (pOtherCollider->GetObjName() == L"����")
	{
		Logger::Debug(L"Ŀ��� �浹");
		TakeDamage(/*m_pWeapon->damage*/0);
	}
	if (pOtherCollider->GetObjName() == L"���Ƶ��̱�")
	{
		dizzy = true;
		if (m_vecPos.x > pOtherCollider->GetOwner()->GetPos().x)
			m_vecPos.x -= 300 * DT;
		if (m_vecPos.x < pOtherCollider->GetOwner()->GetPos().x)
			m_vecPos.x += 300 * DT;
	}
	if (pOtherCollider->GetObjName() == L"�Ϲ�Ŀ��")
	{
		DELETEOBJECT(this);
	}

}

void CMonster::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CMonster::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�ٴ�")
	{
		--m_groundCounter;
		if (m_groundCounter <= 0)
		{
			m_groundchecker = false;
			Logger::Debug(L"���Ͱ� �̻��ϰ� �浹����");
		}
	}
	if (pOtherCollider->GetObjName() == L"����")
	{
		dizzy = false;
		Logger::Debug(L"Ŀ��� �浹");
	}

}
