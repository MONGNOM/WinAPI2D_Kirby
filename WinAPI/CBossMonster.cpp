#include "framework.h"
#include "CBossMonster.h"
#include "CBossHp.h"
#include "CGameManager.h"

CBossMonster::CBossMonster()
{
	m_pAnimator = nullptr;
	m_pAttackImage = nullptr;
	m_pAttackImage2 = nullptr;
	m_pDieImage = nullptr;
	m_pIdleImage = nullptr;
	m_pMoveImage = nullptr;
	m_pJumpImage = nullptr;
	m_pIceDieImage = nullptr;
 	m_pAttackImageL2 = nullptr;
	m_pBossImageR = nullptr;
	m_pBossImageL = nullptr;
	m_pWeapon = nullptr;
	Attack = true;
	jumpDown = true;
	m_vecLookDir = Vector(-1, 0);
	m_state = State::Fear;
	hp = GAME->BossHp;
	m_jumpSpeed = 0.f;

}

CBossMonster::~CBossMonster()
{
}


void CBossMonster::Init()
{
	CBossHp* BossHP = new CBossHp;
	BossHP->SetPos(550, 537);
	BossHP->SetScale(432, 94);
	ADDOBJECT(BossHP);

	CMonster::Init();
	m_pBossImageR		= RESOURCE->LoadImg(L"BossR", L"Image\\Monster\\King\\kingRight.png");
	m_pBossImageL		= RESOURCE->LoadImg(L"BossL", L"Image\\Monster\\King\\kingLeft.png");

	m_pMoveImage		= RESOURCE->LoadImg(L"BossMonsterMove", L"Image\\Monster\\King\\KingisBack.png");
	m_pDieImage			= RESOURCE->LoadImg(L"BossMonsterDie", L"Image\\Monster\\King\\KingDie.png");
	m_pAttackImage		= RESOURCE->LoadImg(L"BossMonsterAttack", L"Image\\Monster\\King\\KingJump.png");
	m_pAttackImage2		= RESOURCE->LoadImg(L"BossMonsterAttack2", L"Image\\Monster\\King\\king1.png");
	m_pIdleImage		= RESOURCE->LoadImg(L"BossMonsterIdle", L"Image\\Monster\\King\\KingisBack.png");
	m_pAttackImageL2	= RESOURCE->LoadImg(L"BossMonsterAttack2L", L"Image\\Monster\\King\\king1L.png");

	m_pAnimator = new CAnimator;
	//오른쪽
	m_pAnimator->CreateAnimation(L"IdleR", m_pBossImageR, Vector(0.f, 0.f), Vector(200.f, 203.f), Vector(280.f, 0.f), 0.2f, 4);
	m_pAnimator->CreateAnimation(L"WalkR", m_pBossImageR, Vector(1120.f, 0.f), Vector(200.f, 203.f), Vector(280.f, 0.f), 0.15f, 4);
	m_pAnimator->CreateAnimation(L"DieR",	m_pBossImageR, Vector(280.f, 1500.f), Vector(210.f, 203.f), Vector(290.f, 0.f), 0.15f, 3);
	m_pAnimator->CreateAnimation(L"AttackR", m_pBossImageR, Vector(0.f, 580.f), Vector(210.f, 250.f), Vector(280.f, 0.f), 0.2f, 8,false);
	m_pAnimator->CreateAnimation(L"JumpAttackR", m_pBossImageR, Vector(0.f, 900.f), Vector(200.f, 250.f), Vector(280.f, 0.f), 0.15f, 1,false);
	m_pAnimator->CreateAnimation(L"DizzyR", m_pBossImageR, Vector(0.f, 1500.f), Vector(200.f, 203.f), Vector(280.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"FearR", m_pBossImageR, Vector(0.f, 1200.f), Vector(200.f, 203.f), Vector(280.f, 0.f), 0.1f, 2);
	m_pAnimator->CreateAnimation(L"DisappearR", m_pBossImageR, Vector(1120.f, 1500.f), Vector(200.f, 203.f), Vector(280.f, 0.f), 0.15f, 3);
	m_pAnimator->CreateAnimation(L"JumpR", m_pBossImageR, Vector(0.f, 300.f), Vector(200.f, 203.f), Vector(280.f, 0.f), 0.15f, 4, false);
	m_pAnimator->CreateAnimation(L"JumpDownR", m_pBossImageR, Vector(1400.f, 300.f), Vector(200.f, 203.f), Vector(280.f, 0.f), 0.f, 1);

	// 왼쪽
	m_pAnimator->CreateAnimation(L"IdleL", m_pBossImageL, Vector(2040.f, 0.f), Vector(200.f, 203.f), Vector(-280.f, 0.f), 0.2f, 4);
	m_pAnimator->CreateAnimation(L"WalkL", m_pBossImageL, Vector(920.f, 0.f), Vector(200.f, 203.f), Vector(-280.f, 0.f), 0.15f, 4);
	m_pAnimator->CreateAnimation(L"DieL", m_pBossImageL, Vector(1750.f, 1500.f), Vector(210.f, 203.f), Vector(-290.f, 0.f), 0.25f, 3);
	m_pAnimator->CreateAnimation(L"AttackL", m_pBossImageL, Vector(2040.f, 580.f), Vector(210.f, 250.f), Vector(-280.f, 0.f), 0.2f, 8,false);
	m_pAnimator->CreateAnimation(L"JumpAttackL", m_pBossImageL, Vector(2040.f, 900.f), Vector(200.f, 250.f), Vector(-280.f, 0.f), 0.15f, 1,false);
	m_pAnimator->CreateAnimation(L"DizzyL", m_pBossImageL, Vector(2040.f, 1500.f), Vector(200.f, 203.f), Vector(-280.f, 0.f), 0.15f, 1);
	m_pAnimator->CreateAnimation(L"FearL", m_pBossImageL, Vector(2040.f, 1200.f), Vector(200.f, 203.f), Vector(-280.f, 0.f), 0.1f, 2);
	m_pAnimator->CreateAnimation(L"DisappearL", m_pBossImageL, Vector(920.f, 1500.f), Vector(200.f, 203.f), Vector(-280.f, 0.f), 0.15f, 3);
	m_pAnimator->CreateAnimation(L"JumpL", m_pBossImageL, Vector(2040.f, 300.f), Vector(200.f, 203.f), Vector(-280.f, 0.f), 0.15f, 4, false);
	m_pAnimator->CreateAnimation(L"JumpDownL", m_pBossImageL, Vector(640.f, 300.f), Vector(200.f, 203.f), Vector(-280.f, 0.f), 0.f, 1);

	collider->SetColliderScale(800, 300);

	m_pAnimator->Play(L"IdleR", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(170, 180), Vector(0, 0));

}

void CBossMonster::Update()
{ 
	
	// 중력 다시 업데이트에서 체크한번 해야함
	// 공중에서 망치 어택했을때 콜라이더 안따라옴 그거 체크 

	m_jumpSpeed -= m_gravity * DT;

	Logger::Debug(bossstate);
	GAME->BossHp = hp;
	collider->SetPos(m_vecPos);

	CMonster::Update();
	switch (m_state)
	{
	case CBossMonster::State::Idle:
		IdleState();
		break;
	case CBossMonster::State::Walk:
		WalkState();
		break;
	case CBossMonster::State::Attack:
		AttackState();
		break;
	case CBossMonster::State::JumpAttack:
		JumpAttackState();
		break;
	case CBossMonster::State::Die:
		DieState();
		break;
	case CBossMonster::State::Dizzy:
		DizzyState();
		break;
	case CBossMonster::State::Jump:
		JumpState();
		break;
	case CBossMonster::State::JumpDown:
		JumpDownState();
		break;
	case CBossMonster::State::Fear:
		FearState();
		break;
	case CBossMonster::State::Disappear:
		DisappearState();
		break;
	default:
		break;
	}

	if (dizzy) m_state = State::Dizzy;

	AnimatorUpdate();
}

void CBossMonster::Render()
{
}

void CBossMonster::Release()
{
}
void CBossMonster::IdleState()
{
	if (hp <= 0) m_state = State::Die;
	
	idleTimer += DT;
	if (m_vecLookDir.x == 1)
	{
		bossstate = L"IdleR";
		if (idleTimer > 2.f)
		{
			idleTimer = 0;
			m_state = State::Walk;
		}
	}
	if (m_vecLookDir.x == -1)
	{
		bossstate = L"IdleL";
		if (idleTimer > 2.f)
		{
			idleTimer = 0;
			m_state = State::Walk;
		}
	}
}

void CBossMonster::WalkState()
{
	walkTimer += DT;
	if (m_vecLookDir.x == 1)
	{
		bossstate = L"WalkR";
		m_vecPos.x += 50 * DT;
		if (walkTimer > 5.f)
		{
			walkTimer = 0;
			BasicAttack();
		}
	}
	if (m_vecLookDir.x == -1)
	{
		bossstate = L"WalkL";
		m_vecPos.x -= 50 * DT;
		if (walkTimer > 5.f)
		{
			walkTimer = 0;
			BasicAttack();
		}

	}
	
}

void CBossMonster::AttackState()
{
	attackTimer += DT;

	if (m_pWeapon == nullptr)
		MonsterAttackCollider();

	if (m_vecLookDir.x == 1)
	{
		bossstate = L"AttackR";
		if (attackTimer > 1.6f)
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
		bossstate = L"AttackL";
		if (attackTimer > 1.6f)
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


void CBossMonster::DieState()
{
	dieTimer += DT;
		if (m_vecLookDir.x == 1)
		{
			bossstate = L"DieR";
			if (dieTimer > 1.f)
			{
				dieTimer = 0;
 				m_state = State::Disappear;
			}
		}
		if (m_vecLookDir.x == -1)
		{
			bossstate = L"DieL";
			if (dieTimer > 1.f)
			{
				dieTimer = 0;
				m_state = State::Disappear;
			}
		}
}

void CBossMonster::DizzyState()
{
	dieTimer += DT;
	if (m_vecLookDir.x == 1)
	{
		bossstate = L"DizzyR";
		if (dieTimer > 0.5f)
		{
			m_state = State::Idle;
			dieTimer = 0;
			dizzy = false;

		}
	}
	if (m_vecLookDir.x == -1)
	{
		bossstate = L"DizzyL";
		if (dieTimer > 0.5f)
		{
			m_state = State::Idle;
			dizzy = false;
			dieTimer = 0;
		}
	}
}

void CBossMonster::JumpState()
{
	m_vecPos.y -= m_jumpSpeed * DT;

	if (m_vecLookDir.x == 1)
	{
		m_vecPos.x += 50 * DT;

		bossstate = L"JumpR";
		if (m_jumpSpeed < 0)
		{
			JumpDown();
		}
	}
	if (m_vecLookDir.x == -1)
	{
		m_vecPos.x -= 50 * DT;

		bossstate = L"JumpL";
		if (m_jumpSpeed < 0)
		{
			JumpDown();
		}
	}
}

void CBossMonster::JumpDownState()
{
		m_vecPos.y -= m_jumpSpeed * DT;
	if (m_vecLookDir.x == 1)
	{
		bossstate = L"JumpDownR";
		if (m_groundchecker)
		{
			m_state = State::Idle;
		}
	}
	if (m_vecLookDir.x == -1)
	{
		bossstate = L"JumpDownL";
		if (m_groundchecker)
		{
			m_state = State::Idle;
		}
	}
}

void CBossMonster::JumpAttackState()
{
	m_vecPos.y -= m_jumpSpeed * DT;
	if (m_pWeapon == nullptr)
		MonsterAttackCollider();

	if (m_vecLookDir.x == 1)
	{
		bossstate = L"JumpAttackR";
		if (m_groundchecker)
		{
			if (m_pWeapon != nullptr)
			{
				DELETEOBJECT(m_pWeapon);
				m_pWeapon = nullptr;
			}
			m_state = State::Idle;
		}
	}
	if (m_vecLookDir.x == -1)
	{
		bossstate = L"JumpAttackL";
		if (m_groundchecker)
		{
			if (m_pWeapon != nullptr)
			{
				DELETEOBJECT(m_pWeapon);
				m_pWeapon = nullptr;
			}
			m_state = State::Idle;
		}
	}
}

void CBossMonster::FearState()
{
	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * DT;
	}
	attackTimer += DT;
	if (m_vecLookDir.x == 1)
	{
		
		bossstate = L"FearR";

		if (attackTimer > 1.15f)
		{
			attackTimer = 0;
			m_state = State::Idle;
		}
	}
	if (m_vecLookDir.x == -1)
	{
		bossstate = L"FearL";
		if (attackTimer > 1.15f)
		{
			attackTimer = 0;
			m_state = State::Idle;
		}
	}
}

void CBossMonster::DisappearState()
{
	dieTimer += DT;
	if (m_vecLookDir.x == 1)
	{
		bossstate = L"DisappearR";
		if (dieTimer > 1.f)
		{
			dieTimer = 0;
			DELETEOBJECT(this); DELETEOBJECT(collider);
		}
	}
	if (m_vecLookDir.x == -1)
	{
		bossstate = L"DisappearL";
		if (dieTimer > 1.f)
		{
			dieTimer = 0;
			DELETEOBJECT(this); DELETEOBJECT(collider);
		}
	}
}

void CBossMonster::BasicAttack()
{
	if (Attack)
	{
		Attack = false;
		m_state = State::Attack;
	}
	else
	{
		m_jumpSpeed = 300.f;
		m_state = State::Jump;
		Attack = true;
	}
}

void CBossMonster::JumpDown()
{
	if (jumpDown)
	{
		jumpDown = false;
		m_state = State::JumpDown;
	}
	else
	{
		jumpDown = true;
		m_state = State::JumpAttack;
	}
}

void CBossMonster::MonsterAttackCollider()
{
	m_pWeapon = new CMonsterWeapon();
	if (m_vecLookDir.x == -1)
	{
		m_pWeapon->SetMonsterWeaponScale(150, 200);
		m_pWeapon->SetPos(m_vecPos.x - 150, m_vecPos.y);
	}
	if (m_vecLookDir.x == 1)
	{
		m_pWeapon->SetMonsterWeaponScale(150, 200);
		m_pWeapon->SetPos(m_vecPos.x + 150, m_vecPos.y);
	}
	ADDOBJECT(m_pWeapon);
}

void CBossMonster::AnimatorUpdate()
{
	m_pAnimator->Play(bossstate, false);
}
