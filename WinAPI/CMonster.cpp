#include "framework.h"
#include "CMonster.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CKirbyWeapon.h"
#include "CNomalKirby.h"

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
	
}

CMonster::~CMonster()
{
}

void CMonster::Init()
{

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
		CKirbyWeapon* pWeapon = (CKirbyWeapon*)pOtherCollider->GetOwner();
		TakeDamage(pWeapon->damage);
		Logger::Debug(L"Ŀ��� �浹");
	}

	
	
	if (pOtherCollider->GetObjName() == L"�Ϲ�Ŀ��")
	{
		CNomalKirby* normalKirby = (CNomalKirby*)pOtherCollider->GetOwner();
		if (normalKirby->eat)
		{
			DELETEOBJECT(this);
		}
	}

}


void CMonster::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"���Ƶ��̱�")
	{
		dizzy = true;
		if (m_vecPos.x > pOtherCollider->GetOwner()->GetPos().x)
			m_vecPos.x -= 500 * DT;
		if (m_vecPos.x < pOtherCollider->GetOwner()->GetPos().x)
			m_vecPos.x += 500 * DT;
	}
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
