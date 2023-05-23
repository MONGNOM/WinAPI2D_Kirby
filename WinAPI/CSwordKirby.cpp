#include "framework.h"
#include "CSwordKirby.h"

CSwordKirby::CSwordKirby()
{
	attackTimer = 0;
	m_state = State::Idle;
	m_pAnimator = nullptr;
	m_pIdleImage = nullptr;
	m_pMoveImage = nullptr;
	m_pRunImage = nullptr;
	m_pDownImage = nullptr;
	m_pFlyImage = nullptr;
	m_pJumpImage = nullptr;
	m_pAttackImage = nullptr;
}

CSwordKirby::~CSwordKirby()
{
}

void CSwordKirby::Init()
{
	m_pIdleImage = RESOURCE->LoadImg(L"IceKirbyIdleL", L"Image\\Kirby\\sword kirby.png");
	m_pAttackImage = RESOURCE->LoadImg(L"IceKirbyAttack", L"Image\\Kirby\\sword kirby.png");
	m_pMoveImage = RESOURCE->LoadImg(L"IceKirbyW", L"Image\\Kirby\\sword kirby.png");
	m_pRunImage = RESOURCE->LoadImg(L"IceKirbyRun", L"Image\\Kirby\\sword kirby.png");
	m_pDownImage = RESOURCE->LoadImg(L"IceKirbyDown", L"Image\\Kirby\\sword kirby.png");
	m_pFlyImage = RESOURCE->LoadImg(L"IceKirbyFly", L"Image\\Kirby\\sword kirby.png");
	m_pJumpImage = RESOURCE->LoadImg(L"IceKirbyJump", L"Image\\Kirby\\sword kirby.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IdleR", m_pIdleImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"IdleL", m_pIdleImage, Vector(70.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"RW", m_pMoveImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"LW", m_pMoveImage, Vector(630.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"RRun", m_pRunImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"LRun", m_pRunImage, Vector(490.f, 104.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"RDown", m_pDownImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"LDown", m_pDownImage, Vector(70.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"RAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.04f, 8, false);
	m_pAnimator->CreateAnimation(L"LAttack", m_pAttackImage, Vector(490.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.04f, 6, false);
	m_pAnimator->CreateAnimation(L"RFly", m_pFlyImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 5);
	m_pAnimator->CreateAnimation(L"LFly", m_pFlyImage, Vector(620.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.08f, 5);
	m_pAnimator->CreateAnimation(L"RFlying", m_pFlyImage, Vector(340.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 5);
	m_pAnimator->CreateAnimation(L"LFlying", m_pFlyImage, Vector(270.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.08f, 4);
	m_pAnimator->CreateAnimation(L"RJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.08f, 9, false);
	m_pAnimator->CreateAnimation(L"LJump", m_pJumpImage, Vector(630.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.08f, 9, false);
	m_pAnimator->CreateAnimation(L"RJumping", m_pJumpImage, Vector(480.f, 0.f), Vector(65.f, 50.f), Vector(70.f, 0.f), 0.08f, 2);
	m_pAnimator->CreateAnimation(L"LJumping", m_pJumpImage, Vector(130.f, 100.f), Vector(65.f, 50.f), Vector(-70.f, 0.f), 0.08f, 2);
	m_pAnimator->CreateAnimation(L"RAttacking", m_pAttackImage, Vector(420.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.06f, 2);
	m_pAnimator->CreateAnimation(L"LAttacking", m_pAttackImage, Vector(210.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.06f, 2);
	m_pAnimator->Play(L"IdleR", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Circle, Vector(20, 20), Vector(0, 0));
}

void CSwordKirby::Update()
{
	CKirby::Update();
	switch (m_state)
	{
	case State::Idle:
		IdleState();
		break;
	case State::Walk:
		WalkState();
		break;
	case State::Run:
		RunState();
		break;
	case State::Jump:
		JumpState();
		break;
	case State::Sit:
		SitState();
		break;
	case State::Fly:
		FlyState();
		break;
	case State::Attack:
		AttackState();
		break;
	case State::JumpingDown:
		JumpingDownState();
		break;
	case State::Flying:
		FlyingState();
		break;
	case State::Attacking:
		AttackingState();
		break;
	default:
		break;
	}
	AnimatorUpdate();
}




void CSwordKirby::Render()
{
}

void CSwordKirby::Release()
{
}

void CSwordKirby::AnimatorUpdate()
{
	m_pAnimator->Play(swordkirbystate, false);
}

#pragma region 상태패턴 함수

void CSwordKirby::Jump()
{
	m_jumpSpeed = 300;
	fallTimer = 0;
}

void CSwordKirby::IdleState()
{
	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * DT;
	}
	if (m_vecLookDir.x == -1)
	{
		swordkirbystate = L"IdleL";
	}
	else if (m_vecLookDir.x == 1)
	{
		swordkirbystate = L"IdleR";
	}
	if (BUTTONSTAY(VK_LEFT))
	{
		if (lastLeftInputTime < TIME_DASHABLE)
			m_state = State::Run;
		else
			m_state = State::Walk;

		lastLeftInputTime = 0;
	}
	if (BUTTONSTAY(VK_RIGHT))
	{
		if (lastRightInputTime < TIME_DASHABLE)
			m_state = State::Run;
		else
			m_state = State::Walk;

		lastRightInputTime = 0;
	}
	if (BUTTONDOWN('S'))
	{
		m_state = State::Attack;
	}
	if (BUTTONSTAY(VK_DOWN))
	{
		m_state = State::Sit;
	}
	if (BUTTONSTAY(VK_UP))
	{
		m_state = State::Fly;
	}
	if (BUTTONDOWN('A'))
	{
		Jump();
		m_state = State::Jump;
	}
}

void CSwordKirby::WalkState()
{
	m_fSpeed = 100.f;
	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * DT;
	}
	if (BUTTONSTAY(VK_LEFT))
	{
		m_vecMoveDir.x = -1;
		m_vecPos.x -= m_fSpeed * DT;
		swordkirbystate = L"LW";
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		m_vecMoveDir.x = 1;
		m_vecPos.x += m_fSpeed * DT;
		swordkirbystate = L"RW";

	}

	if (!(BUTTONSTAY(VK_RIGHT) || BUTTONSTAY(VK_LEFT)))
	{
		m_state = State::Idle;
	}
	if (BUTTONDOWN('S'))
	{
		m_state = State::Attack;
	}
	if (BUTTONSTAY(VK_DOWN))
	{
		m_state = State::Sit;
	}
	if (BUTTONSTAY(VK_UP))
	{
		m_state = State::Fly;
	}
	if (BUTTONDOWN('A'))
	{
		Jump();
		m_state = State::Jump;
	}
}

void CSwordKirby::RunState()
{
	m_fSpeed = 200.0f;
	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * DT;
	}
	if (BUTTONSTAY(VK_LEFT))
	{
		m_vecMoveDir.x = -1;
		swordkirbystate = L"LRun";
		m_vecPos.x -= m_fSpeed * DT;
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		m_vecMoveDir.x = 1;
		swordkirbystate = L"RRun";
		m_vecPos.x += m_fSpeed * DT;
	}
	if (!(BUTTONSTAY(VK_RIGHT) || BUTTONSTAY(VK_LEFT)))
	{
		m_state = State::Idle;
	}
	if (BUTTONDOWN('S'))
	{
		m_state = State::Attack;
	}
	if (BUTTONSTAY(VK_DOWN))
	{
		m_state = State::Sit;
	}
	if (BUTTONSTAY(VK_UP))
	{
		m_state = State::Fly;
	}
	if (BUTTONDOWN('A'))
	{
		Jump();
		m_state = State::Jump;
	}
}

void CSwordKirby::JumpState()
{
	m_vecPos.y -= m_jumpSpeed * DT;

	if (m_vecLookDir.x == -1)
	{
		swordkirbystate = L"LJump";
		if (BUTTONSTAY(VK_RIGHT))
		{
			m_vecPos.x += m_fSpeed * DT;
			m_vecMoveDir.x = 1;
		}
		else if (BUTTONSTAY(VK_LEFT))
		{
			m_vecPos.x -= m_fSpeed * DT;
			m_vecMoveDir.x = -1;
		}
		if (m_jumpSpeed < 0)
		{
			m_state = State::JumpingDown;
		}
	}
	if (m_vecLookDir.x == 1)
	{
		swordkirbystate = L"RJump";
		if (BUTTONSTAY(VK_RIGHT))
		{
			m_vecPos.x += m_fSpeed * DT;
			m_vecMoveDir.x = 1;
		}
		else if (BUTTONSTAY(VK_LEFT))
		{
			m_vecPos.x -= m_fSpeed * DT;
			m_vecMoveDir.x = -1;
		}
		if (m_jumpSpeed < 0)
		{
			m_state = State::JumpingDown;
		}
	}
}

void CSwordKirby::SitState()
{
	if (m_vecLookDir.x == 1)
	{
		swordkirbystate = L"RDown";
		if (BUTTONSTAY(VK_DOWN) && BUTTONSTAY(VK_LEFT))
		{
			m_vecLookDir.x = -1;
			swordkirbystate = L"LDown";
		}
	}
	else if (m_vecLookDir.x == -1)
	{
		swordkirbystate = L"LDown";
		if (BUTTONSTAY(VK_DOWN) && BUTTONDOWN(VK_LEFT))
		{
			m_vecLookDir.x = 1;
			swordkirbystate = L"RDown";
		}
	}
	if (!BUTTONSTAY(VK_DOWN))
		m_state = State::Idle;
}

void CSwordKirby::FlyState()
{
	flyTimer += DT;
	//땅에있고  && 0.5초동안 플라이
	m_fSpeed = 100;
	if (m_vecLookDir.x == 1)
	{
		swordkirbystate = L"RFly";
		if (flyTimer > 0.4f)
		{
			flyTimer = 0;
			m_state = State::Flying;
		}
	}
	else if (m_vecLookDir.x == -1)
	{
		swordkirbystate = L"LFly";
		if (flyTimer > 0.4f)
		{
			flyTimer = 0;
			m_state = State::Flying;

		}
	}
	else if (BUTTONUP(VK_UP))
	{
		m_jumpSpeed = 0;
		m_state = State::JumpingDown;
	}

	if (BUTTONDOWN('S'))
	{
		m_state = State::Attack;
	}

}

void CSwordKirby::AttackState()
{
	attackTimer += DT;

	if (m_vecLookDir.x == -1)
	{
		swordkirbystate = L"LAttack";
		if (attackTimer > 0.4f)
		{
			attackTimer = 0;
			m_state = State::Attacking;
		}
	}
	if (m_vecLookDir.x == 1)
	{
		swordkirbystate = L"RAttack";
		if (attackTimer > 0.4f)
		{
			attackTimer = 0;
			m_state = State::Attacking;
		}
	}
	if (BUTTONUP('S'))
	{
		m_state = State::Idle;
	}
}

void CSwordKirby::AttackingState()
{
	if (m_vecLookDir.x == -1)
	{
		swordkirbystate = L"LAttacking";
	}
	if (m_vecLookDir.x == 1)
	{
		swordkirbystate = L"RAttacking";
	}
	if (BUTTONUP('S'))
	{
		m_state = State::Idle;
	}
}

void CSwordKirby::JumpingDownState()
{
	m_vecPos.y -= m_jumpSpeed * DT;
	if (m_vecLookDir.x == -1)
	{
		swordkirbystate = L"LJumping";
		if (BUTTONSTAY(VK_RIGHT))
		{
			m_vecPos.x += m_fSpeed * DT;
			m_vecMoveDir.x = 1;
		}
		if (BUTTONSTAY(VK_LEFT))
		{
			m_vecPos.x -= m_fSpeed * DT;
			m_vecMoveDir.x = -1;
		}
		if (m_groundchecker == true)
		{
			m_state = State::Idle;
		}
	}
	if (m_vecLookDir.x == 1)
	{
		swordkirbystate = L"RJumping";
		if (BUTTONSTAY(VK_RIGHT))
		{
			m_vecPos.x += m_fSpeed * DT;
			m_vecMoveDir.x = 1;
		}
		if (BUTTONSTAY(VK_LEFT))
		{
			m_vecPos.x -= m_fSpeed * DT;
			m_vecMoveDir.x = -1;
		}
		if (m_groundchecker == true)
		{
			m_state = State::Idle;
		}
	}
	if (BUTTONDOWN('A'))
	{
		flyTimer = 0;
		m_state = State::Fly;
	}
	//점프 다운 구현중
	m_groundchecker = false;

}

void CSwordKirby::FlyingState()
{
	m_vecPos.y += m_gravity * 0.1f * DT;

	if (BUTTONSTAY(VK_UP))
		m_vecPos.y -= m_fSpeed * DT;

	if (BUTTONSTAY(VK_RIGHT))
	{
		m_vecPos.x += m_fSpeed * DT;
		m_vecLookDir.x = 1;
	}
	else if (BUTTONSTAY(VK_LEFT))
	{
		m_vecPos.x -= m_fSpeed * DT;
		m_vecLookDir.x = -1;
	}

	if (m_vecLookDir.x == 1)
	{
		swordkirbystate = L"RFlying";
	}
	else if (m_vecLookDir.x == -1)
	{
		swordkirbystate = L"LFlying";
	}

	if (BUTTONDOWN('S'))
	{
		m_jumpSpeed = 0;
		m_state = State::JumpingDown;
	}

	m_groundchecker = false;

}

#pragma endregion

