#include "framework.h"
#include "CSwordMonster.h"
#include "CNomalKirby.h"

CSwordMonster::CSwordMonster()
{
	m_vecLookDir = Vector(-1, 0);
	m_pAnimator = nullptr;
	m_pAttackImage = nullptr;
	m_pAttackImage2 = nullptr;
	m_pLAttackImage = nullptr;
	m_pLAttackImage2 = nullptr;
	m_pLIdleImage = nullptr;
	m_pDieImage = nullptr;
	m_pIdleImage = nullptr;
	m_pMoveImage = nullptr;
	m_pIceDieImage = nullptr;
	m_strName = L"칼몬스터";

	m_state = State::Idle;
	hp = 2;
}

CSwordMonster::~CSwordMonster()
{
	
}


void CSwordMonster::Init()
{
	attackCollider = new CMonsterAttackCollider();
	attackCollider->SetSwordMonster(this);
	ADDOBJECT(attackCollider);
	attackCollider->SetColliderScale(300, 100);

	CMonster::Init();
	m_pMoveImage	= RESOURCE->LoadImg(L"SwordMonsterMove",	L"Image\\Monster\\SwordMonster\\SwordMonster.png");
	m_pDieImage		= RESOURCE->LoadImg(L"SwordMonsterDie",		L"Image\\Monster\\SwordMonster\\SwordMonster.png");
	m_pAttackImage	= RESOURCE->LoadImg(L"SwordMonsterAttack",	L"Image\\Monster\\SwordMonster\\SwordMonsterAttack.png");
	m_pAttackImage2	= RESOURCE->LoadImg(L"SwordMonsterAttack2",	L"Image\\Monster\\SwordMonster\\SwordMonsterAttack2.png");
	m_pIdleImage	= RESOURCE->LoadImg(L"SwordMonsterIdle",	L"Image\\Monster\\SwordMonster\\SwordMonster.png");

	m_pLAttackImage		= RESOURCE->LoadImg(L"LSwordMonsterAttack", L"Image\\Monster\\SwordMonster\\SwordMonsterAttackL.png");
	m_pLAttackImage2	= RESOURCE->LoadImg(L"LSwordMonsterAttack2", L"Image\\Monster\\SwordMonster\\SwordMonsterAttack2L.png");
	m_pLIdleImage		= RESOURCE->LoadImg(L"LSwordMonsterIdle", L"Image\\Monster\\SwordMonster\\SwordMonsterL.png");
	
	m_pIceDieImage = RESOURCE->LoadImg(L"BIceDie", L"Image\\MonstericeStatebig.png");
	

	m_pAnimator = new CAnimator;
	//오른쪽
	m_pAnimator->CreateAnimation(L"IdleR",		m_pIdleImage,		Vector(0.f, 0.f), Vector(125.f, 101.f), Vector(125.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"WalkR",		m_pMoveImage,		Vector(248.f, 0.f), Vector(125.f, 101.f), Vector(132.f, 0.f), 0.15f, 6);
	m_pAnimator->CreateAnimation(L"DieR",		m_pDieImage,		Vector(0.f, 490.f), Vector(145.f, 100.f), Vector(145.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"AttackR",	m_pAttackImage,		Vector(0.f, 20.f), Vector(420.f, 170.f), Vector(420.f, 0.f), 0.07f, 9, false);
	m_pAnimator->CreateAnimation(L"Attack2R",	m_pAttackImage2,	Vector(0.f, 0.f), Vector(420.f, 110.f), Vector(420.f, 0.f), 0.07f, 6, false);
	m_pAnimator->CreateAnimation(L"DizzyR",		m_pDieImage,		Vector(0.f, 490.f), Vector(145.f, 100.f), Vector(0.f, 0.f), 0.15f, 1);
	
	// 왼쪽
	m_pAnimator->CreateAnimation(L"IdleL",		m_pLIdleImage,		Vector(1172.f, 0.f), Vector(125.f, 101.f), Vector(-125.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"WalkL",		m_pLIdleImage,		Vector(920.f, 0.f), Vector(125.f, 101.f), Vector(-132.f, 0.f), 0.15f, 6);
	m_pAnimator->CreateAnimation(L"DieL",		m_pLIdleImage,		Vector(1150.f, 490.f), Vector(145.f, 100.f), Vector(-145.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"AttackL",	m_pLAttackImage,	Vector(3360.f, 20.f), Vector(420.f, 170.f), Vector(-420.f, 0.f), 0.07f, 9, false);
	m_pAnimator->CreateAnimation(L"Attack2L",	m_pLAttackImage2,	Vector(2100.f, 0.f), Vector(420.f, 110.f), Vector(-420.f, 0.f), 0.07f, 6, false);
	m_pAnimator->CreateAnimation(L"DizzyL",		m_pLIdleImage,		Vector(1150.f, 490.f), Vector(145.f, 100.f), Vector(0.f, 0.f), 0.15f, 1); 

	m_pAnimator->CreateAnimation(L"BIceDie", m_pIceDieImage, Vector(0.f, 0.f), Vector(99.f, 100.f), Vector(0.f, 0.f), 0.5f, 1);

	m_pAnimator->Play(L"IdleR", false);
	AddComponent(m_pAnimator);
	collider->SetColliderScale(250, 100);
	AddCollider(ColliderType::Rect, Vector(100, 100), Vector(0, 0));
}

void CSwordMonster::Update()
{
	CMonster::Update();

	collider->SetPos(m_vecPos);
	attackCollider->SetPos(m_vecPos);

	switch (m_state)
	{
	case CSwordMonster::State::Idle:
		IdleState();
		break;
	case CSwordMonster::State::Walk:
		WalkState();
		break;
	case CSwordMonster::State::Attack:
		AttackState();
		break;
	case CSwordMonster::State::Attack2:
		AttackState2();
		break;
	case CSwordMonster::State::Die:
		DieState();
		break;
	case State::Dizzy:
		DizzyState();
	default:
		break;
	}

	
	if (dizzy)
	{
		m_state =State::Dizzy;
		dizzy = false;
	}
	
	AnimatorUpdate();
}

void CSwordMonster::IdleState()
{
	
	idleTimer += DT;
	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * DT;
	}
	if (m_vecLookDir.x == 1)
	{
		swordstate = L"IdleR";
		if (idleTimer > 2.f)
		{
			idleTimer = 0;
			m_state = State::Walk;
		}
	}
	if (m_vecLookDir.x == -1)
	{
		swordstate = L"IdleL";
		if (idleTimer > 2.f)
		{
			idleTimer = 0;
			m_state = State::Walk;
		}
	}

}

void CSwordMonster::WalkState()
{
	walkTimer += DT;
	if (m_vecLookDir.x == 1)
	{
		swordstate = L"WalkR";
		m_vecPos.x += 50 * DT;
		if (walkTimer > 5.f)
		{
			walkTimer = 0;
			m_state = State::Attack;
		}
	}
	if (m_vecLookDir.x == -1)
	{
		swordstate = L"WalkL";
		m_vecPos.x -= 50 * DT;
		if (walkTimer > 5.f)
		{
			walkTimer = 0;
			m_state = State::Attack;
		}
	}
}

void CSwordMonster::AttackState()
{
	if (m_pWeapon == nullptr)
		MonsterAttackCollider();
	else
	{
		if (m_vecLookDir.x == -1)
		{
			m_pWeapon->SetPos(m_vecPos.x - 70, m_vecPos.y);
		}
		if (m_vecLookDir.x == 1)
		{
			m_pWeapon->SetPos(m_vecPos.x + 70, m_vecPos.y);
		}
	}
	attackTimer += DT;
	if (m_vecLookDir.x == 1)
	{
		swordstate = L"AttackR";
		if (attackTimer > 0.7f)
		{
			attackTimer = 0;
			m_state = State::Attack2;
			if (m_pWeapon != nullptr)
			{
				DELETEOBJECT(m_pWeapon);
				m_pWeapon = nullptr;
			}

		}
	}
	if (m_vecLookDir.x == -1)
	{
		swordstate = L"AttackL";
		if (attackTimer > 0.7f)
		{
			attackTimer = 0;
			m_state = State::Attack2;
			if (m_pWeapon != nullptr)
			{
				DELETEOBJECT(m_pWeapon);
				m_pWeapon = nullptr;
			}

		}
	}
}

void CSwordMonster::AttackState2()
{
	attackTimer += DT;
	
	if (m_pWeapon == nullptr)
		MonsterAttackCollider();
	if (m_vecLookDir.x == -1)
	{
		m_pWeapon->SetPos(m_vecPos.x - 70, m_vecPos.y);
	}
	if (m_vecLookDir.x == 1)
	{
		m_pWeapon->SetPos(m_vecPos.x + 70, m_vecPos.y);
	}
	if (m_vecLookDir.x == 1)
	{
		swordstate = L"Attack2R";
		if (attackTimer > 0.7f)
		{
			if (m_pWeapon != nullptr)
			{
				DELETEOBJECT(m_pWeapon);
				m_pWeapon = nullptr;
			}
			attackTimer = 0;
			m_state = State::Idle;
		}
	}
	if (m_vecLookDir.x == -1)
	{
		swordstate = L"Attack2L";
		if (attackTimer > 0.7f)
		{
			if (m_pWeapon != nullptr)
			{
				DELETEOBJECT(m_pWeapon);
				m_pWeapon = nullptr;
			}
			attackTimer = 0;
			m_state = State::Idle;
		}
	}
}

void CSwordMonster::DieState()
{
	
	dieTimer += DT;
	if (iceDie)
	{
		if (m_vecLookDir.x == 1)
		{
			swordstate = L"BIceDie";
			if (dieTimer > 1.f)
			{
				dieTimer = 0;
				DeleteObject();
			}
		}
		if (m_vecLookDir.x == -1)
		{
			swordstate = L"BIceDie";
			if (dieTimer > 1.f)
			{
				dieTimer = 0;
				DeleteObject();
			}
		}
	}
	else
	{
		if (m_vecLookDir.x == 1)
		{
			swordstate = L"DieR";
			if (dieTimer > 1.f)
			{
				dieTimer = 0;
				DeleteObject();

			}
		}
		if (m_vecLookDir.x == -1)
		{
			swordstate = L"DieL";
			if (dieTimer > 1.f)
			{
				dieTimer = 0;
				DeleteObject();
			}
		}
	}
}

void CSwordMonster::DizzyState()
{
	if (hp <= 0)
	{
		m_state = State::Die;
		SOUND->Play(DeathSound, 0.1f, false);
	}
	dieTimer += DT;
	if (m_vecLookDir.x == 1)
	{
		swordstate = L"DizzyR";
		if (dieTimer > 0.5f)
		{
			m_state = State::Idle;
			dieTimer = 0;
		}
	}
	if (m_vecLookDir.x == -1)
	{
		swordstate = L"DizzyL";
		if (dieTimer > 0.5f)
		{
			m_state = State::Idle;
			dieTimer = 0;
		}
	}
}

void CSwordMonster::MonsterAttackCollider()
{
	m_pWeapon = new CMonsterWeapon();
	if (m_vecLookDir.x == -1)
	{
		m_pWeapon->SetMonsterWeaponScale(70, 100);
		m_pWeapon->SetPos(m_vecPos.x - 70, m_vecPos.y);
	}
	if (m_vecLookDir.x == 1)
	{
		m_pWeapon->SetMonsterWeaponScale(70, 100);
		m_pWeapon->SetPos(m_vecPos.x + 70, m_vecPos.y);
	}
	ADDOBJECT(m_pWeapon);
}

void CSwordMonster::DeleteObject()
{
	DELETEOBJECT(this); 
	DELETEOBJECT(collider);
	DELETEOBJECT(attackCollider);
	if (m_pWeapon != nullptr)
	{
		DELETEOBJECT(m_pWeapon);
		m_pWeapon = nullptr;
	}
	
}

void CSwordMonster::Render()
{
}

void CSwordMonster::Release()
{
}

void CSwordMonster::OnCollisionEnter(CCollider* pOtherCollider)
{
	CMonster::OnCollisionEnter(pOtherCollider);
	if (pOtherCollider->GetObjName() == L"일반커비")
	{
		CNomalKirby* normalKirby = (CNomalKirby*)pOtherCollider->GetOwner();
		if (normalKirby->eat)
		{
			if (m_pWeapon != nullptr && attackCollider != nullptr)
			{
				DELETEOBJECT(m_pWeapon);
				DELETEOBJECT(attackCollider);
			}
		}
	}

}
void CSwordMonster::AnimatorUpdate()
{
	m_pAnimator->Play(swordstate, false);
}
