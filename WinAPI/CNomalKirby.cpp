#include "framework.h"
#include "CNomalKirby.h"
#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"


CNomalKirby::CNomalKirby()
{
	m_state			= State::Idle;
	m_pAnimator		= nullptr;
	m_pIdleLImage   = nullptr;
	m_pIdleRImage   = nullptr;
	m_pMoveLImage   = nullptr;
	m_pMoveRImage   = nullptr;
	m_pRunImage     = nullptr;
	m_pDownImage    = nullptr;
	m_pFlyImage	    = nullptr;
	m_pJumpImage	= nullptr;
	m_pJumpingImage = nullptr;
	m_pAttackImage	= nullptr;
}

CNomalKirby::~CNomalKirby()
{

}

void CNomalKirby::Init()
{
	m_pIdleLImage	= RESOURCE->LoadImg(L"KirbyIdleL",	L"Image\\Kirby\\Basic\\KirbyIdleL.png"	);
	m_pIdleRImage	= RESOURCE->LoadImg(L"KirbyIdleR",	L"Image\\Kirby\\Basic\\KirbyIdleR.png"	);
	m_pMoveLImage	= RESOURCE->LoadImg(L"KirbyLW",		L"Image\\Kirby\\Basic\\KirbyLW.png"		);
	m_pMoveRImage	= RESOURCE->LoadImg(L"KirbyRW",		L"Image\\Kirby\\Basic\\KirbyRW.png"		);
	m_pRunImage		= RESOURCE->LoadImg(L"KirbyRun",	L"Image\\Kirby\\Basic\\KirbyRun.png"	);
	m_pDownImage	= RESOURCE->LoadImg(L"KirbyDown",	L"Image\\Kirby\\Basic\\KirbyDown.png"	);
	m_pFlyImage		= RESOURCE->LoadImg(L"KirbyFly",	L"Image\\Kirby\\Basic\\KirbyFly.png"	);
	m_pJumpImage	= RESOURCE->LoadImg(L"KirbyJump", L"Image\\Kirby\\Basic\\KirbyJump.png"		);
	m_pAttackImage	= RESOURCE->LoadImg(L"KirbyAttack",	L"Image\\Kirby\\Basic\\KirbyEat.png"	);

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IdleR",		m_pIdleRImage,	Vector(  0.f,   0.f), Vector( 45.f,  43.f), Vector(  45.f,   0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"IdleL",		m_pIdleLImage,	Vector(  0.f,   0.f), Vector( 45.f,  43.f), Vector(  45.f,   0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"LW",			m_pMoveLImage,	Vector(  0.f,   0.f), Vector( 60.f,  50.f), Vector(  70.f,   0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"RW",			m_pMoveRImage,	Vector(  0.f,   0.f), Vector( 60.f,  50.f), Vector(  70.f,   0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"RRun",		m_pRunImage,	Vector(  0.f,   0.f), Vector( 60.f,  50.f), Vector(  70.f,   0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"LRun",		m_pRunImage,	Vector(490.f, 104.f), Vector( 60.f,  50.f), Vector( -70.f,   0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"LDown",		m_pDownImage,	Vector(  0.f, 100.f), Vector( 50.f,  50.f), Vector(  50.f,   0.f), 10.0f, 1);
	m_pAnimator->CreateAnimation(L"RDown",		m_pDownImage,	Vector(  0.f,   0.f), Vector( 50.f,  50.f), Vector(  50.f,   0.f), 10.0f, 1);
	m_pAnimator->CreateAnimation(L"RFly",		m_pFlyImage,	Vector(  0.f,   0.f), Vector( 60.f,  50.f), Vector(  70.f,   0.f), 0.08f, 19, false);
	m_pAnimator->CreateAnimation(L"RFlying",	m_pFlyImage,	Vector(400.f,   0.f), Vector( 85.f,  50.f), Vector(  70.f,   0.f), 0.08f, 6);
	m_pAnimator->CreateAnimation(L"LFly",		m_pFlyImage,	Vector(  0.f, 100.f), Vector( 60.f,  50.f), Vector(  70.f,   0.f), 0.08f, 19, false);
	m_pAnimator->CreateAnimation(L"LFlying",	m_pFlyImage,	Vector(400.f, 100.f), Vector( 85.f,  50.f), Vector(  70.f,   0.f), 0.08f, 6);
	m_pAnimator->CreateAnimation(L"RJump",		m_pJumpImage,	Vector(  0.f,   0.f), Vector( 50.f,  50.f), Vector(  58.f,   0.f), 0.06f, 9,  false);
	m_pAnimator->CreateAnimation(L"LJump",		m_pJumpImage,	Vector(  0.f,  90.f), Vector( 50.f,  50.f), Vector(  58.f,   0.f), 0.06f, 9,  false);
	m_pAnimator->CreateAnimation(L"RJumping",	m_pJumpImage,	Vector(400.f,   0.f), Vector( 50.f,  50.f), Vector(  58.f,   0.f), 0.08f, 2);
	m_pAnimator->CreateAnimation(L"LJumping",	m_pJumpImage,	Vector(400.f,  90.f), Vector( 50.f,  50.f), Vector(  58.f,   0.f), 0.08f, 2);
	m_pAnimator->CreateAnimation(L"RAttack",	m_pAttackImage,	Vector(0.f,  0.f), Vector( 57.f,  57.f), Vector(  70.f,   0.f), 0.08f, 5);
	m_pAnimator->CreateAnimation(L"LAttack",	m_pAttackImage,	Vector(0.f,  95.f), Vector( 57.f,  57.f), Vector(  70.f,   0.f), 0.08f, 5);

	m_pAnimator->Play(L"IdleR", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Circle, Vector(20, 20), Vector(0, 0));
}


void CNomalKirby::Update()
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
	default:
		break;
	}
	AnimatorUpdate();
}

void CNomalKirby::Render()
{
}


void CNomalKirby::AnimatorUpdate()
{
	m_pAnimator->Play(Icekirbystate, false);
}

void CNomalKirby::Jump()
{
	m_jumpSpeed = 300;
	fallTimer = 0;
}

void CNomalKirby::IdleState()
{
	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * DT;
	}
	if (m_vecLookDir.x == -1)
	{
		Icekirbystate = L"IdleL";
	}
	else if (m_vecLookDir.x == 1)
	{
		Icekirbystate = L"IdleR";
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

void CNomalKirby::WalkState()
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
		Icekirbystate = L"LW";
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		m_vecMoveDir.x = 1;
		m_vecPos.x += m_fSpeed * DT;
		Icekirbystate = L"RW";

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

void CNomalKirby::RunState()
{
	m_fSpeed = 200.0f;
	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * DT;
	}
	if (BUTTONSTAY(VK_LEFT))
	{
		m_vecMoveDir.x = -1;
		Icekirbystate = L"LRun";
		m_vecPos.x -= m_fSpeed * DT;
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		m_vecMoveDir.x = 1;
		Icekirbystate = L"RRun";
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

void CNomalKirby::JumpState() 
{
	m_vecPos.y -= m_jumpSpeed * DT;

	if (m_vecLookDir.x == -1)
	{
		Icekirbystate = L"LJump";
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
		Icekirbystate = L"RJump";
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

void CNomalKirby::SitState()
{
	if (m_vecLookDir.x == 1)
	{
		Icekirbystate = L"RDown";
		if (BUTTONSTAY(VK_DOWN) && BUTTONSTAY(VK_LEFT))
		{
			m_vecLookDir.x = -1;
			Icekirbystate = L"LDown";
		}
	}
	else if (m_vecLookDir.x == -1)
	{
		Icekirbystate = L"LDown";
		if (BUTTONSTAY(VK_DOWN) && BUTTONDOWN(VK_LEFT))
		{
			m_vecLookDir.x = 1;
			Icekirbystate = L"RDown";
		}
	}
	if (!BUTTONSTAY(VK_DOWN))
	m_state = State::Idle;
}

void CNomalKirby::FlyState()
{
	flyTimer += DT;
	//땅에있고  && 0.5초동안 플라이
	m_fSpeed = 100;
	if (m_vecLookDir.x == 1)
	{
		Icekirbystate = L"RFly";
		if (flyTimer > 0.4f)
		{ 
			flyTimer = 0;
			m_state = State::Flying;
		}
	}
	else if (m_vecLookDir.x == -1)
	{
		Icekirbystate = L"LFly";
		if (flyTimer > 0.4f)
		{
			flyTimer = 0;
			m_state = State::Flying;

		}
	}
	else if(BUTTONUP(VK_UP))
	{
		m_jumpSpeed = 0;
		m_state = State::JumpingDown;
	}
	
	if (BUTTONDOWN('S'))
	{
		m_state = State::Attack;
	}

}

void CNomalKirby::Attack()
{
	if (m_vecLookDir.x == -1)
	{
		Icekirbystate = L"LAttack";
	}
	if (m_vecLookDir.x == 1)
	{
		Icekirbystate = L"RAttack";
	}
	if (BUTTONUP('S'))
	{
		m_state = State::Idle;
	}

}

void CNomalKirby::AttackState()
{
	Attack();
}


void CNomalKirby::JumpingDownState()
{
	m_vecPos.y -= m_jumpSpeed * DT;
	if (m_vecLookDir.x == -1)
	{
		Icekirbystate = L"LJumping";
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
		Icekirbystate = L"RJumping";
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

void CNomalKirby::FlyingState()
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
		Icekirbystate = L"RFlying";
	}
	else if (m_vecLookDir.x == -1)
	{
		Icekirbystate = L"LFlying";
	}
	
	if(BUTTONDOWN('S'))
	{
		m_jumpSpeed = 0;
		m_state = State::JumpingDown;
	}

	m_groundchecker = false;

}


void CNomalKirby::Release()
{

}


