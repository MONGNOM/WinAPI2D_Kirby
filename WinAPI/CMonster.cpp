#include "framework.h"
#include "CMonster.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CKirbyWeapon.h"
#include "CNomalKirby.h"
#include "CMonsterAttackCollider.h"
#include "CMonsterWeapon.h"

CMonster::CMonster()
{
	collider = nullptr;
	m_layer = Layer::Monster;
	m_fSpeed = 200.f;
	m_vecLookDir = Vector(1, 0);
	m_groundchecker = false;
	m_groundCounter = 0;
	m_gravity = 300;
	dieTimer = 0;
	idleTimer = 0;
	attackTimer = 0;
	walkTimer = 0;
	hp = 0;
	dizzy = false;
	iceDie = false;
	DamageSound = RESOURCE->LoadSound(L"MonsterDamageSound", L"Sound\\Damage.wav");
	DeathSound	= RESOURCE->LoadSound(L"MonsterDeathSound", L"Sound\\MonsterDeath.wav");

}

CMonster::~CMonster()
{
}

void CMonster::Init()
{
	collider = new CHitCollider();
	collider->SetMonster(this);
	ADDOBJECT(collider);
}

void CMonster::Update()
{
	

}

void CMonster::Render()
{
	
}

void CMonster::Release()
{
}

void CMonster::TakeDamage(int damage)
{
	SOUND->Play(DamageSound, 0.1f, false);
	hp -= damage;
	dizzy = true;
}



CMonster* CMonster::GetMonster()
{
	return this;
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
	}
	
	
	
	if (pOtherCollider->GetObjName() == L"�Ϲ�Ŀ��")
	{
		CNomalKirby* normalKirby = (CNomalKirby*)pOtherCollider->GetOwner();
		if (normalKirby->eat)
		{
			DELETEOBJECT(this);
			DELETEOBJECT(collider);
			SOUND->Play(DeathSound, 0.1f, false);
		}
		if (this != nullptr)
		{
			normalKirby->eating = true;
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
	if (pOtherCollider->GetObjName() == L"�󸮱�")
	{
		CKirbyWeapon* pWeapon = (CKirbyWeapon*)pOtherCollider->GetOwner();
		TakeDamage(pWeapon->damage);
		iceDie = true;
	}
	else
	{
		iceDie = false;
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
