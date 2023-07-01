#include "framework.h"
#include "CIceMonster.h"
#include "WinAPI.h"
#include "CCollider.h"
#include "CTimeManager.h"
#include "CImage.h"
#include "CAnimator.h"
#include "CEventManager.h"
#include "CRenderManager.h"
#include "CKirbyWeapon.h"
#include "CNomalKirby.h"



CIceMonster::CIceMonster()
{
	m_vecLookDir = Vector(-1, 0);
	m_state = State::Walk;
	m_pAnimator = nullptr;
	m_pMoveImage = nullptr;
	m_pDieImage = nullptr;
	m_pAttackImage = nullptr;
	m_pIceDieImage = nullptr;
	iceAttack = nullptr;
	hp = 2;
	m_strName = L"얼음몬스터";
}

CIceMonster::~CIceMonster()
{
}



void CIceMonster::Init()
{

	CMonster::Init();
	m_pMoveImage	= RESOURCE->LoadImg(L"IceMonsterMove", L"Image\\Monster\\IceMonster\\IceMonsterWalk.png");
	m_pDieImage		= RESOURCE->LoadImg(L"IceMonsterDie", L"Image\\Monster\\IceMonster\\IceMonsterDie.png");
	m_pAttackImage	= RESOURCE->LoadImg(L"IceMonsterAttack", L"Image\\Monster\\IceMonster\\IceMonsterAttackPose.png");

	m_pIceDieImage	= RESOURCE->LoadImg(L"IceDie", L"Image\\MonstericeStatesmall.png");


	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"WalkR", m_pMoveImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.15f, 3);
	m_pAnimator->CreateAnimation(L"WalkL", m_pMoveImage, Vector(145.f, 100.f), Vector(50.f, 58.f), Vector(-70.f, 0.f), 0.15f, 3);	
	m_pAnimator->CreateAnimation(L"DieR", m_pDieImage, Vector(0.f, 0.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"DieL", m_pDieImage, Vector(0.f, 100.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"DizzyR", m_pDieImage, Vector(0.f, 0.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 1);
	m_pAnimator->CreateAnimation(L"DizzyL", m_pDieImage, Vector(0.f, 100.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 1);
	m_pAnimator->CreateAnimation(L"AttackR", m_pAttackImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.2f, 3, false);
	m_pAnimator->CreateAnimation(L"AttackL", m_pAttackImage, Vector(135.f, 120.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.2f, 3, false);

	attackCollider = new CMonsterAttackCollider();
	attackCollider->SetIceMonster(this);
	ADDOBJECT(attackCollider);

	m_pAnimator->Play(L"WalkR", false);
	AddComponent(m_pAnimator);
	collider->SetColliderScale(200, 100);
	attackCollider->SetColliderScale(250, 100);
	AddCollider(ColliderType::Circle, Vector(20, 20), Vector(0, 0));

}

void CIceMonster::Update()
{
	CMonster::Update();
	collider->SetPos(m_vecPos);
	attackCollider->SetPos(m_vecPos);

	switch (m_state)
	{
	case CIceMonster::State::Walk:
		WalkState();
		break;
	case CIceMonster::State::Die:
		DieState();
		break;
	case CIceMonster::State::Attack:
		AttackState();
		break;
	case State::Dizzy:
		DizzyState();
	default:
		break;
	}
	if (dizzy)
	{
		dizzy = false;
		m_state = State::Dizzy;
	}
	if (hp <= 0)
	{
		m_state = State::Die;
		SOUND->Play(DeathSound, 0.1f, false);
	}
	
	AnimatorUpdate();
}

void CIceMonster::Render()
{
}

void CIceMonster::Release()
{
}



void CIceMonster::WalkState()
{
	walkTimer += DT;
	
	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * DT;
	}
	
	if (m_vecLookDir.x == 1)
	{
		iceState = L"WalkR";
		m_vecPos.x += 50 * DT;
		if (walkTimer > 3.f)
		{
			walkTimer = 0;
			m_state = State::Attack;
		}
	}
	if (m_vecLookDir.x == -1)
	{
		iceState = L"WalkL";
		m_vecPos.x -= 50 * DT;
		if (walkTimer > 3.f)
		{
			walkTimer = 0;
			m_state = State::Attack;
		}
	}
}

void CIceMonster::DieState()
{
	dieTimer += DT;
	if (iceDie)
	{
		if (m_vecLookDir.x == 1)
		{
			iceState = L"IceDie";
			if (dieTimer > 1.f)
			{
				dieTimer = 0;
				DELETEOBJECT(iceAttack);
				DELETEOBJECT(this); DELETEOBJECT(collider); DELETEOBJECT(attackCollider);
			}
		}
		if (m_vecLookDir.x == -1)
		{
			iceState = L"IceDie";
			if (dieTimer > 1.f)
			{
				dieTimer = 0;
				DELETEOBJECT(iceAttack);
				DELETEOBJECT(this); DELETEOBJECT(collider); DELETEOBJECT(attackCollider);
			}
		}
	}
	else
	{
		if (m_vecLookDir.x == 1)
		{
			iceState = L"DieR";
			if (dieTimer > 1.f)
			{
				dieTimer = 0;
				DELETEOBJECT(iceAttack);
				DELETEOBJECT(this); DELETEOBJECT(collider); DELETEOBJECT(attackCollider);
			}
		}
		if (m_vecLookDir.x == -1)
		{
			iceState = L"DieL";
			if (dieTimer > 1.f)
			{
				dieTimer = 0;
				DELETEOBJECT(iceAttack);
				DELETEOBJECT(this); DELETEOBJECT(collider); DELETEOBJECT(attackCollider);
			}
		}
	}
	
}

void CIceMonster::AttackState()
{
	attackTimer += DT;

	if (iceAttack == nullptr)
		MonsterAttackCollider();
	else
	{
		if (m_vecLookDir.x == -1)
		{
			iceAttack->SetPos(m_vecPos.x - 70, m_vecPos.y);
		}
		if (m_vecLookDir.x == 1)
		{
			iceAttack->SetPos(m_vecPos.x + 70, m_vecPos.y);
		}
	}
	if (m_vecLookDir.x == 1)
	{
		iceState = L"AttackR";
		if (attackTimer > 2.0f)
		{
			if (iceAttack != nullptr)
			{
				DELETEOBJECT(iceAttack);
				iceAttack = nullptr;
			}
			attackTimer = 0;
			m_state = State::Walk;

		}
	}
	if (m_vecLookDir.x == -1)
	{
		iceState = L"AttackL";
		if (attackTimer > 2.0f)
		{
			if (iceAttack != nullptr)
			{
				DELETEOBJECT(iceAttack);
				iceAttack = nullptr;
			}
			attackTimer = 0;
			m_state = State::Walk;

		}
	}
}

void CIceMonster::DizzyState()
{
	
	dieTimer += DT;
	if (m_vecLookDir.x == 1)
	{
		iceState = L"DizzyR";
		if (dieTimer > 0.5f)
		{
			dieTimer = 0;
			m_state = State::Walk;
		}
	}
	if (m_vecLookDir.x == -1)
	{
		iceState = L"DizzyL";
		if (dieTimer > 0.5f)
		{
			dieTimer = 0;
			m_state = State::Walk;
		}
	}
}

void CIceMonster::MonsterAttackCollider()
{
	iceAttack = new CMonsterIceAttack();
	if (m_vecLookDir.x == -1)
	{
		iceAttack->SetMonsterWeaponScale(100, 50);
		iceAttack->SetPos(m_vecPos.x - 70, m_vecPos.y);
	}
	if (m_vecLookDir.x == 1)
	{
		iceAttack->SetMonsterWeaponScale(100, 50);
		iceAttack->SetPos(m_vecPos.x + 70 ,m_vecPos.y);
	}
	ADDOBJECT(iceAttack);
}

void CIceMonster::OnCollisionEnter(CCollider* pOtherCollider)
{
	CMonster::OnCollisionEnter(pOtherCollider);
	if (pOtherCollider->GetObjName() == L"일반커비")
	{
		CNomalKirby* normalKirby = (CNomalKirby*)pOtherCollider->GetOwner();
		if (normalKirby->eat)
		{
			if (iceAttack != nullptr && attackCollider != nullptr)
			{
				DELETEOBJECT(iceAttack);
				DELETEOBJECT(attackCollider);
				iceAttack = nullptr;
				attackCollider = nullptr;
			}
		}
	}

}


void CIceMonster::AnimatorUpdate()
{
	m_pAnimator->Play(iceState, false);
}
