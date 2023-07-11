#include "framework.h"
#include "CBossMonster.h"
#include "CBossHp.h"
#include "CGameManager.h"

CBossMonster::CBossMonster()
{
	m_pAnimator = nullptr;
	m_pBossImageR = nullptr;
	m_pBossImageL = nullptr;
	m_pWeapon = nullptr;
	Attack = true;
	jumpDown = true;
	m_vecLookDir = Vector(-1, 0);
	m_state = State::Fear;
	hp = GAME->BossHp;
	m_jumpSpeed = 0.f;
	JumpSound = RESOURCE->LoadSound(L"BossJumpSound", L"Sound\\BossJump.wav");
	AttackSound = RESOURCE->LoadSound(L"BossAttackSound", L"Sound\\BossAttack.wav");
	ShoutSound = RESOURCE->LoadSound(L"BossShoutSound", L"Sound\\BossShout.wav");
	WalkSound = RESOURCE->LoadSound(L"BossWalkSound", L"Sound\\BossWalk.wav");
	DeathSound = RESOURCE->LoadSound(L"BossDeathSound", L"Sound\\BossDeath.wav");
	GAME->invincible = 1.0f;
	bossDeath = false;

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


	m_pAnimator = new CAnimator;
	//������
	m_pAnimator->CreateAnimation(L"IdleR", m_pBossImageR, Vector(0.f, 0.f), Vector(200.f, 203.f), Vector(280.f, 0.f), 0.2f, 4);
	m_pAnimator->CreateAnimation(L"WalkR", m_pBossImageR, Vector(1120.f, 0.f), Vector(200.f, 203.f), Vector(280.f, 0.f), 0.5f, 4);
	m_pAnimator->CreateAnimation(L"DieR",	m_pBossImageR, Vector(280.f, 1500.f), Vector(210.f, 203.f), Vector(290.f, 0.f), 0.15f, 3);
	m_pAnimator->CreateAnimation(L"AttackR", m_pBossImageR, Vector(0.f, 580.f), Vector(210.f, 250.f), Vector(280.f, 0.f), 0.2f, 8,false);
	m_pAnimator->CreateAnimation(L"JumpAttackR", m_pBossImageR, Vector(0.f, 900.f), Vector(200.f, 250.f), Vector(280.f, 0.f), 0.15f, 1,false);
	m_pAnimator->CreateAnimation(L"DizzyR", m_pBossImageR, Vector(0.f, 1500.f), Vector(200.f, 203.f), Vector(280.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"FearR", m_pBossImageR, Vector(0.f, 1200.f), Vector(200.f, 203.f), Vector(280.f, 0.f), 0.1f, 2);
	m_pAnimator->CreateAnimation(L"DisappearR", m_pBossImageR, Vector(1120.f, 1500.f), Vector(200.f, 203.f), Vector(280.f, 0.f), 0.15f, 3);
	m_pAnimator->CreateAnimation(L"JumpR", m_pBossImageR, Vector(0.f, 300.f), Vector(200.f, 203.f), Vector(280.f, 0.f), 0.15f, 4, false);
	m_pAnimator->CreateAnimation(L"JumpDownR", m_pBossImageR, Vector(1400.f, 300.f), Vector(200.f, 203.f), Vector(280.f, 0.f), 0.f, 1);

	// ����
	m_pAnimator->CreateAnimation(L"IdleL", m_pBossImageL, Vector(2040.f, 0.f), Vector(200.f, 203.f), Vector(-280.f, 0.f), 0.2f, 4);
	m_pAnimator->CreateAnimation(L"WalkL", m_pBossImageL, Vector(920.f, 0.f), Vector(200.f, 203.f), Vector(-280.f, 0.f), 0.5f, 4);
	m_pAnimator->CreateAnimation(L"DieL", m_pBossImageL, Vector(1750.f, 1500.f), Vector(210.f, 203.f), Vector(-290.f, 0.f), 0.25f, 3);
	m_pAnimator->CreateAnimation(L"AttackL", m_pBossImageL, Vector(2040.f, 580.f), Vector(210.f, 250.f), Vector(-280.f, 0.f), 0.2f, 8,false);
	m_pAnimator->CreateAnimation(L"JumpAttackL", m_pBossImageL, Vector(2040.f, 900.f), Vector(200.f, 250.f), Vector(-280.f, 0.f), 0.15f, 1,false);
	m_pAnimator->CreateAnimation(L"DizzyL", m_pBossImageL, Vector(2040.f, 1500.f), Vector(200.f, 203.f), Vector(-280.f, 0.f), 0.15f, 1);
	m_pAnimator->CreateAnimation(L"FearL", m_pBossImageL, Vector(2040.f, 1200.f), Vector(200.f, 203.f), Vector(-280.f, 0.f), 0.1f, 2);
	//m_pAnimator->CreateAnimation(L"DisappearL", m_pBossImageL, Vector(920.f, 1500.f), Vector(200.f, 203.f), Vector(-280.f, 0.f), 0.15f, 3);
	m_pAnimator->CreateAnimation(L"DisappearL", m_pBossImageL, Vector(0.f, 0.f), Vector(1.f, 1.f), Vector(1.f, 0.f), 0.f, 1);
	m_pAnimator->CreateAnimation(L"JumpL", m_pBossImageL, Vector(2040.f, 300.f), Vector(200.f, 203.f), Vector(-280.f, 0.f), 0.15f, 4, false);
	m_pAnimator->CreateAnimation(L"JumpDownL", m_pBossImageL, Vector(640.f, 300.f), Vector(200.f, 203.f), Vector(-280.f, 0.f), 0.f, 1);

	collider->SetColliderScale(800, 300);

	m_pAnimator->Play(L"IdleR", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(170, 180), Vector(0, 0));
	Shout();
}

void CBossMonster::Update()
{ 
	m_jumpSpeed -= m_gravity * DT;

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
	if (dizzy)
	{
		BossEffect();
		

		m_state = State::Dizzy;
		dizzy = false;
	}
	if (hp <= 0)
	{
		m_state = State::Die;
	}
	idleTimer += DT;
	if (m_vecLookDir.x == 1)
	{
		bossstate = L"IdleR";
		if (idleTimer > 2.f)
		{
			SOUND->Play(WalkSound, 0.1f, true);
			idleTimer = 0;
			m_state = State::Walk;
		}
	}
	if (m_vecLookDir.x == -1)
	{
		bossstate = L"IdleL";
		if (idleTimer > 2.f)
		{
			SOUND->Play(WalkSound, 0.1f, true);
			idleTimer = 0;
			m_state = State::Walk;
		}
	}
}

void CBossMonster::WalkState()
{
	if (dizzy)
	{
		BossEffect();
		m_state = State::Dizzy;
		dizzy = false;
	}
	/*m_jumpSpeed = 10;

	m_vecPos.y -= m_jumpSpeed * DT;*/
	if (m_vecPos.y <= 200)
	{
		m_vecPos.y += m_jumpSpeed * DT;
	}
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
	if (dizzy)
	{
		BossEffect();
		m_state = State::Dizzy;
		dizzy = false;
	}
	attackTimer += DT;
	if (m_pWeapon == nullptr)
		MonsterAttackCollider();

	if (m_vecLookDir.x == 1)
	{
		m_vecPos.x += 50 * DT;
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
		m_vecPos.x -= 50 * DT;
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
	bossDeath = true;
	dieTimer += DT;
		if (m_vecLookDir.x == 1)
		{
			bossstate = L"DieR";
			if (dieTimer > 1.f)
			{
				Effect(m_vecPos.x + 10, m_vecPos.y);
				effect->MonsterDeathEffect();
				SOUND->Play(DeathSound, 0.1f, false);
				dieTimer = 0;
 				m_state = State::Disappear;
			}
		}
		if (m_vecLookDir.x == -1)
		{
			bossstate = L"DieL";
			if (dieTimer > 1.f) 
			{
				Effect(m_vecPos.x + 10,m_vecPos.y);
				effect->MonsterDeathEffect();
				SOUND->Play(DeathSound, 0.1f, false);
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
	if (m_pWeapon == nullptr)
		MonsterAttackCollider();
	else
	{
		if (m_vecLookDir.x == -1)
		{
			m_pWeapon->SetPos(m_vecPos.x - 150, m_vecPos.y);
		}
		if (m_vecLookDir.x == 1)
		{
			m_pWeapon->SetPos(m_vecPos.x + 150, m_vecPos.y);
		}
	}
	if (m_vecLookDir.x == 1)
	{
		bossstate = L"JumpDownR";
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
		bossstate = L"JumpDownL";
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

void CBossMonster::JumpAttackState()
{
	m_vecPos.y -= m_jumpSpeed * DT;
	if (m_pWeapon == nullptr)
		MonsterAttackCollider();
	else
	{
		if (m_vecLookDir.x == -1)
		{
			m_pWeapon->SetPos(m_vecPos.x - 150, m_vecPos.y);
		}
		if (m_vecLookDir.x == 1)
		{
			m_pWeapon->SetPos(m_vecPos.x + 150, m_vecPos.y);
		}
	}
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

		if (attackTimer > 0.8f)
		{
			SOUND->Pause(ShoutSound);
			attackTimer = 0;
			m_state = State::Idle;
		}
	}
	if (m_vecLookDir.x == -1)
	{
		bossstate = L"FearL";
		if (attackTimer > 1.8f)
		{
			SOUND->Pause(ShoutSound);
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
		if (dieTimer > 0.42f)
		{
			dieTimer = 0;
			DELETEOBJECT(effect);
			DELETEOBJECT(this); DELETEOBJECT(collider);
		}
	}
	if (m_vecLookDir.x == -1)
	{
	
		bossstate = L"DisappearL";
		if (dieTimer > 0.42f)
		{
			dieTimer = 0;
			DELETEOBJECT(effect);
			DELETEOBJECT(this); DELETEOBJECT(collider);
		}
	}
}

void CBossMonster::Shout()
{
	SOUND->Play(ShoutSound, 0.5f, true);
}

void CBossMonster::BasicAttack()
{
	SOUND->Pause(WalkSound);
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
	SOUND->Play(AttackSound, 0.3f, false);
	m_pWeapon = new CMonsterWeapon();
	star = new BossMakeStar();
	if (m_vecLookDir.x == -1)
	{
		m_pWeapon->SetMonsterWeaponScale(150, 200);
		m_pWeapon->SetPos(m_vecPos.x -150, m_vecPos.y);
		star->SetPos(m_vecPos.x - 150, m_vecPos.y + 70);
	}
	if (m_vecLookDir.x == 1)
	{
		m_pWeapon->SetMonsterWeaponScale(150, 200);
		m_pWeapon->SetPos(m_vecPos.x + 150, m_vecPos.y);
		star->SetPos(m_vecPos.x + 150, m_vecPos.y + 70);

	}
	ADDOBJECT(m_pWeapon);
	ADDOBJECT(star);
}

void CBossMonster::AnimatorUpdate()
{
	m_pAnimator->Play(bossstate, false);
}
