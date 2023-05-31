#include "framework.h"
#include "CSwordMonster.h"

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
	m_strName = L"Ä®¸ó½ºÅÍ";

	m_state = State::Idle;
	hp = 2;
}

CSwordMonster::~CSwordMonster()
{
	
}


void CSwordMonster::Init()
{
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
	//¿À¸¥ÂÊ
	m_pAnimator->CreateAnimation(L"IdleR",		m_pIdleImage,		Vector(0.f, 0.f), Vector(125.f, 101.f), Vector(125.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"WalkR",		m_pMoveImage,		Vector(248.f, 0.f), Vector(125.f, 101.f), Vector(132.f, 0.f), 0.15f, 6);
	m_pAnimator->CreateAnimation(L"DieR",		m_pDieImage,		Vector(0.f, 490.f), Vector(145.f, 100.f), Vector(145.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"AttackR",	m_pAttackImage,		Vector(0.f, 0.f), Vector(135.f, 110.f), Vector(280.f, 0.f), 0.07f, 9);
	m_pAnimator->CreateAnimation(L"Attack2R",	m_pAttackImage2,	Vector(0.f, 0.f), Vector(135.f, 112.f), Vector(280.f, 0.f), 0.07f, 6);
	m_pAnimator->CreateAnimation(L"DizzyR",		m_pDieImage,		Vector(0.f, 490.f), Vector(145.f, 100.f), Vector(0.f, 0.f), 0.15f, 1);
	
	// ¿ÞÂÊ
	m_pAnimator->CreateAnimation(L"IdleL",		m_pLIdleImage,		Vector(1172.f, 0.f), Vector(125.f, 101.f), Vector(-125.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"WalkL",		m_pLIdleImage,		Vector(920.f, 0.f), Vector(125.f, 101.f), Vector(-132.f, 0.f), 0.15f, 6);
	m_pAnimator->CreateAnimation(L"DieL",		m_pLIdleImage,		Vector(1150.f, 490.f), Vector(145.f, 100.f), Vector(-145.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"AttackL",	m_pLAttackImage,	Vector(2400.f, 0.f), Vector(135.f, 110.f), Vector(-280.f, 0.f), 0.07f, 9);
	m_pAnimator->CreateAnimation(L"Attack2L",	m_pLAttackImage2,	Vector(1565.f, 0.f), Vector(135.f, 112.f), Vector(-280.f, 0.f), 0.07f, 6);
	m_pAnimator->CreateAnimation(L"DizzyL",		m_pLIdleImage,		Vector(1150.f, 490.f), Vector(145.f, 100.f), Vector(0.f, 0.f), 0.15f, 1); 

	m_pAnimator->CreateAnimation(L"BIceDie", m_pIceDieImage, Vector(0.f, 0.f), Vector(99.f, 100.f), Vector(0.f, 0.f), 0.5f, 1);

	m_pAnimator->Play(L"IdleR", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(100, 100), Vector(0, 0));
}

void CSwordMonster::Update()
{
	
	CMonster::Update();
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

	if (dizzy) m_state = State::Dizzy;
	if (hp <= 0) m_state = State::Die;
	AnimatorUpdate();
}

void CSwordMonster::IdleState()
{
	if (m_vecLookDir.x == 1)
	{
		swordstate = L"IdleR";
	}
	if (m_vecLookDir.x == -1)
	{
		swordstate = L"IdleL";
	}

}

void CSwordMonster::WalkState()
{
	if (m_vecLookDir.x == 1)
	{
		swordstate = L"WalkR";
		m_vecPos.x += 50 * DT;
	}
	if (m_vecLookDir.x == -1)
	{
		swordstate = L"WalkL";
		m_vecPos.x -= 50 * DT;

	}
}

void CSwordMonster::AttackState()
{
	if (m_vecLookDir.x == 1)
	{
		swordstate = L"AttackR";
	}
	if (m_vecLookDir.x == -1)
	{
		swordstate = L"AttackL";
	}
}

void CSwordMonster::AttackState2()
{
	if (m_vecLookDir.x == 1)
	{
		swordstate = L"Attack2R";
	}
	if (m_vecLookDir.x == -1)
	{
		swordstate = L"Attack2L";
	}
}

void CSwordMonster::DieState()
{
	dieTime += DT;
	if (iceDie)
	{
		if (m_vecLookDir.x == 1)
		{
			swordstate = L"BIceDie";
			if (dieTime > 1.f)
			{
				dieTime = 0;
				DELETEOBJECT(this);
			}
		}
		if (m_vecLookDir.x == -1)
		{
			swordstate = L"BIceDie";
			if (dieTime > 1.f)
			{
				dieTime = 0;
				DELETEOBJECT(this);
			}
		}
	}
	else
	{
		if (m_vecLookDir.x == 1)
		{
			swordstate = L"DieR";
			if (dieTime > 1.f)
			{
				dieTime = 0;
				DELETEOBJECT(this);
			}
		}
		if (m_vecLookDir.x == -1)
		{
			swordstate = L"DieL";
			if (dieTime > 1.f)
			{
				dieTime = 0;
				DELETEOBJECT(this);
			}
		}
	}
}

void CSwordMonster::DizzyState()
{
	dieTime += DT;
	if (m_vecLookDir.x == 1)
	{
		swordstate = L"DizzyR";
		if (dieTime > 0.5f)
		{
			m_state = State::Idle;
			dieTime = 0;
		}
	}
	if (m_vecLookDir.x == -1)
	{
		swordstate = L"DizzyL";
		if (dieTime > 0.5f)
		{
			m_state = State::Idle;
			dieTime = 0;
		}
	}
}

void CSwordMonster::Render()
{
}

void CSwordMonster::Release()
{
}

void CSwordMonster::AnimatorUpdate()
{
	m_pAnimator->Play(swordstate, false);
}
