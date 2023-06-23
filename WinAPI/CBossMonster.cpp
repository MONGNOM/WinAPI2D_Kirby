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
	m_vecLookDir = Vector(-1, 0);
	m_state = State::Idle;
	hp = GAME->BossHp;
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
	m_pMoveImage		= RESOURCE->LoadImg(L"BossMonsterMove", L"Image\\Monster\\King\\KingisBack.png");
	m_pDieImage			= RESOURCE->LoadImg(L"BossMonsterDie", L"Image\\Monster\\King\\KingDie.png");
	m_pAttackImage		= RESOURCE->LoadImg(L"BossMonsterAttack", L"Image\\Monster\\King\\KingJump.png");
	m_pAttackImage2		= RESOURCE->LoadImg(L"BossMonsterAttack2", L"Image\\Monster\\King\\king1.png");
	m_pIdleImage		= RESOURCE->LoadImg(L"BossMonsterIdle", L"Image\\Monster\\King\\KingisBack.png");
	m_pAttackImageL2	= RESOURCE->LoadImg(L"BossMonsterAttack2L", L"Image\\Monster\\King\\king1L.png");

	m_pAnimator = new CAnimator;
	//오른쪽
	m_pAnimator->CreateAnimation(L"IdleR", m_pIdleImage, Vector(0.f, 0.f), Vector(150.f, 180.f), Vector(190.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"WalkR", m_pMoveImage, Vector(770.f, 0.f), Vector(150.f, 180.f), Vector(190.f, 0.f), 0.15f, 4);
	m_pAnimator->CreateAnimation(L"DieR", m_pDieImage, Vector(0.f, 0.f), Vector(180.f, 200.f), Vector(225.f, 0.f), 0.25f, 4,false);
	m_pAnimator->CreateAnimation(L"AttackR", m_pAttackImage, Vector(0.f, 0.f), Vector(165.f, 200.f), Vector(210.f, 0.f), 0.2f, 7,false);
	m_pAnimator->CreateAnimation(L"Attack2R", m_pAttackImage2, Vector(0.f, 0.f), Vector(280.f, 220.f), Vector(375.f, 0.f), 0.15f, 7);
	m_pAnimator->CreateAnimation(L"DizzyR", m_pDieImage, Vector(0.f, 0.f), Vector(180.f, 200.f), Vector(180.f, 0.f), 0.f, 1);

	// 왼쪽
	m_pAnimator->CreateAnimation(L"IdleL", m_pIdleImage, Vector(1350.f, 450.f), Vector(160.f, 180.f), Vector(-190.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"WalkL", m_pMoveImage, Vector(590.f, 430.f), Vector(160.f, 180.f), Vector(-190.f, 0.f), 0.15f, 4);
	m_pAnimator->CreateAnimation(L"DieL", m_pDieImage, Vector(670.f, 290.f), Vector(180.f, 200.f), Vector(-225.f, 0.f), 0.25f, 4, false);
	m_pAnimator->CreateAnimation(L"AttackL", m_pAttackImage, Vector(1260.f, 270.f), Vector(165.f, 210.f), Vector(-210.f, 0.f), 0.2f, 7,false);
	m_pAnimator->CreateAnimation(L"Attack2L", m_pAttackImageL2, Vector(2430.f, 0.f), Vector(280.f, 220.f), Vector(-375.f, 0.f), 0.15f, 7);
	m_pAnimator->CreateAnimation(L"DizzyL", m_pDieImage, Vector(660.f, 300.f), Vector(180.f, 200.f), Vector(0.f, 0.f), 0.15f, 1);

	collider->SetColliderScale(400, 300);

	m_pAnimator->Play(L"DizzyL", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(170, 180), Vector(0, 0));

}

void CBossMonster::Update()
{ 
	GAME->BossHp = hp;
	collider->SetPos(m_vecPos);

	// 시선 돌리는 기준 잡아야함
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
	case CBossMonster::State::Attack2:
		AttackState2();
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
	default:
		break;
	}

	if (dizzy) m_state = State::Dizzy;
	if (hp <= 0) m_state = State::Die;
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
			m_state = State::Attack;
		}
	}
	if (m_vecLookDir.x == -1)
	{
		bossstate = L"WalkL";
		m_vecPos.x -= 50 * DT;
		if (walkTimer > 5.f)
		{
			walkTimer = 0;
			m_state = State::Attack;
		}
	}
}

void CBossMonster::AttackState()
{
	attackTimer += DT;
	if (m_vecLookDir.x == 1)
	{
		bossstate = L"AttackR";
		if (attackTimer > 3.f)
		{
			attackTimer = 0;
			m_state = State::Attack2;
		}
	}
	if (m_vecLookDir.x == -1)
	{
		bossstate = L"AttackL";
		if (attackTimer > 3.f)
		{
			attackTimer = 0;
			m_state = State::Attack2;
		}
	}
}

void CBossMonster::AttackState2()
{
	if (m_pWeapon == nullptr)
		MonsterAttackCollider();

	attackTimer += DT;
	if (m_vecLookDir.x == 1)
	{
		bossstate = L"Attack2R";
		if (attackTimer > 1.5f)
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
		bossstate = L"Attack2L";
		if (attackTimer > 1.5f)
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
				DELETEOBJECT(this); DELETEOBJECT(collider);
			}
		}
		if (m_vecLookDir.x == -1)
		{
			bossstate = L"DieL";
			if (dieTimer > 1.f)
			{
				dieTimer = 0;
				DELETEOBJECT(this); DELETEOBJECT(collider);
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
