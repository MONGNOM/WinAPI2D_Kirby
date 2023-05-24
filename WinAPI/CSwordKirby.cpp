#include "framework.h"
#include "CSwordKirby.h"

CSwordKirby::CSwordKirby()
{
	attackTimer = 0;
	m_state = State::Idle;
	m_pAnimator			= nullptr;
	m_pIdleImage		= nullptr;
	m_pMoveImage		= nullptr;
	m_pRunImage			= nullptr;
	m_pDownImage		= nullptr;
	m_pFlyImage			= nullptr;
	m_pJumpImage		= nullptr;
	m_pAttackImage		= nullptr;
	m_pDownAttackImage	= nullptr;
	m_pJumpingImage		= nullptr;
	m_pFlyingImage		= nullptr;
	m_pJumpAttackImage	= nullptr;
	m_pJumpDownImage	= nullptr;
}

CSwordKirby::~CSwordKirby()
{
}

void CSwordKirby::Init()
{
	m_pIdleImage		= RESOURCE->LoadImg(L"SwordKirbyIdleL",				L"Image\\Kirby\\SwordKirby\\sword kirby Idle.png");
	m_pAttackImage		= RESOURCE->LoadImg(L"SwordKirbyAttack",			L"Image\\Kirby\\SwordKirby\\sword kirby Attack.png");
	m_pMoveImage		= RESOURCE->LoadImg(L"SwordKirbyW",					L"Image\\Kirby\\SwordKirby\\sword kirby Walk1.png");
	m_pRunImage			= RESOURCE->LoadImg(L"SwordKirbyRun",				L"Image\\Kirby\\SwordKirby\\sword kirby Run.png");
	m_pDownImage		= RESOURCE->LoadImg(L"SwordKirbyDown",				L"Image\\Kirby\\SwordKirby\\sword kirby Down.png");
	m_pFlyImage			= RESOURCE->LoadImg(L"SwordKirbyFly",				L"Image\\Kirby\\SwordKirby\\sword kirby Fly.png");
	m_pJumpImage		= RESOURCE->LoadImg(L"SwordKirbyJump",				L"Image\\Kirby\\SwordKirby\\sword kirby Jump.png");
	m_pDownAttackImage	= RESOURCE->LoadImg(L"SwordKirbyDownAttack",		L"Image\\Kirby\\SwordKirby\\sword kirby Down Attack.png");
	m_pFlyingImage		= RESOURCE->LoadImg(L"SwordKirbyFlying",			L"Image\\Kirby\\SwordKirby\\sword kirby Flying.png");
	m_pJumpAttackImage	= RESOURCE->LoadImg(L"SwordKirbyJumpAttack",		L"Image\\Kirby\\SwordKirby\\sword kirby Jump Attack.png");
	m_pJumpDownImage	= RESOURCE->LoadImg(L"SwordKirbyJumpDown",			L"Image\\Kirby\\SwordKirby\\sword kirby jumping down.png");

	//오른쪽
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IdleR",		m_pIdleImage, Vector(0.f, 0.f),		Vector(60.f, 85.f), Vector(62.f, 0.f), 0.8f, 2);//완
	m_pAnimator->CreateAnimation(L"RW",			m_pMoveImage, Vector(0.f, 0.f),		Vector(70.f, 85.f), Vector(70.f, 0.f), 0.05f, 12); // 리소스 수정
	m_pAnimator->CreateAnimation(L"RRun",		m_pRunImage, Vector(0.f, 0.f),		Vector(60.f, 85.f), Vector(63.5f, 0.f), 0.05f, 8);//완
	m_pAnimator->CreateAnimation(L"RDown",		m_pDownImage, Vector(0.f, 0.f),		Vector(70.f, 68.f), Vector(69.f, 0.f), 0.8f, 2);//완
	m_pAnimator->CreateAnimation(L"RAttack",	m_pAttackImage, Vector(0.f, 0.f),	Vector(75.f, 85.f), Vector(70.f, 0.f), 0.04f, 16, false);// 리소스 수정
	m_pAnimator->CreateAnimation(L"RFly",		m_pFlyImage, Vector(0.f, 0.f),		Vector(65.f, 77.f), Vector(70.f, 0.f), 0.08f, 5); //완
	m_pAnimator->CreateAnimation(L"RFlying",	m_pFlyingImage, Vector(0.f, 0.f),	Vector(62.f, 100.f), Vector(63.f, 0.f), 0.08f, 8);//완
	m_pAnimator->CreateAnimation(L"RJump",		m_pJumpImage, Vector(0.f, 0.f),		Vector(65.f, 80.f), Vector(67.f, 0.f), 0.08f, 3, false);//완
	m_pAnimator->CreateAnimation(L"RJumpDown",	m_pJumpDownImage, Vector(0.f, 0.f),	Vector(60.f, 80.f), Vector(60.f, 0.f), 0.08f, 2);//완
	m_pAnimator->CreateAnimation(L"RJumpAttack", m_pJumpAttackImage, Vector(0.f, 0.f), Vector(80.f, 115.f), Vector(80.f, 0.f), 0.06f, 9);// 리소스 수정
	m_pAnimator->CreateAnimation(L"RDownAttack", m_pDownAttackImage, Vector(0.f, 0.f),	Vector(116.f, 44.f), Vector(116.f, 0.f), 0.06f, 2);//완
	
	//왼쪽
	m_pAnimator->CreateAnimation(L"IdleL",		m_pIdleImage, Vector(70.f, 100.f),	Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"LW",			m_pIdleImage, Vector(630.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"LRun",		m_pIdleImage, Vector(490.f, 104.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"LDown",		m_pIdleImage, Vector(70.f, 100.f),	Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"LAttack",	m_pIdleImage, Vector(490.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.04f, 6, false);
	m_pAnimator->CreateAnimation(L"LFly",		m_pIdleImage, Vector(620.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.08f, 5);
	m_pAnimator->CreateAnimation(L"LFlying",	m_pIdleImage, Vector(270.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.08f, 4);
	m_pAnimator->CreateAnimation(L"LJump",		m_pIdleImage, Vector(630.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.08f, 9, false);
	m_pAnimator->CreateAnimation(L"LJumpDown", m_pJumpDownImage, Vector(0.f, 0.f), Vector(60.f, 80.f), Vector(60.f, 0.f), 0.08f, 2);
	m_pAnimator->CreateAnimation(L"LDownAttack", m_pDownAttackImage, Vector(0.f, 0.f), Vector(116.f, 44.f), Vector(116.f, 0.f), 0.06f, 2);// 리소스 수정

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
	case State::JumpAttack:
		JumpAttackState();
		break;
	case State::DownAttack:
		DownAttackState();
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
		if (BUTTONDOWN('S'))
		{
			m_state = State::JumpAttack;
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
		if (BUTTONDOWN('S'))
		{
			m_state = State::JumpAttack;
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
	if (BUTTONDOWN('S'))
		m_state = State::DownAttack;
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
		if (attackTimer > 1.f)
		{
			m_state = State::Idle;
			attackTimer = 0;
		}
	}
	if (m_vecLookDir.x == 1)
	{
		swordkirbystate = L"RAttack";
		if (attackTimer > 1.f)
		{
			m_state = State::Idle;
			attackTimer = 0;
		}
	}
	
}


void CSwordKirby::JumpAttackState()
{
	attackTimer += DT;
	m_vecPos.y -= m_jumpSpeed * DT;

	if (m_vecLookDir.x == 1)
	{
		swordkirbystate = L"RJumpAttack";
	}
	if (m_vecLookDir.x == -1)
	{
		swordkirbystate = L"LJumpAttack";
	}
	else if (attackTimer < 0.5f)
	{
		attackTimer = 0; 
		m_state = State::JumpingDown;
	}
}

void CSwordKirby::DownAttackState()
{
	attackTimer += DT;
	Logger::Debug(L"겅격중!");
	if (m_vecLookDir.x == 1)
	{
		m_vecPos.x += 250 * DT;
		swordkirbystate = L"RDownAttack";
	}
	if (m_vecLookDir.x == -1)
	{
		m_vecPos.x -= 250 * DT;
		swordkirbystate = L"LDownAttack";
	}
	if (attackTimer > 0.5f && BUTTONSTAY(VK_DOWN))
	{
		m_state = State::Sit;
		attackTimer = 0;
	}
	else if (BUTTONUP(VK_DOWN))
		m_state = State::Idle;


}

void CSwordKirby::JumpingDownState()
{
	m_vecPos.y -= m_jumpSpeed * DT;
	if (m_vecLookDir.x == -1)
	{
		swordkirbystate = L"LJumpDown";
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
		swordkirbystate = L"RJumpDown";
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

