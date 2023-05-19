#include "framework.h"
#include "CKirby.h"
#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"

#include "CMissile.h"

CKirby::CKirby()
{
	m_fSpeed	= 0.f;
	m_jumpSpeed = 0.f;
	m_vecPos	= Vector(0, 0);
	m_vecScale	= Vector(100, 100);
	m_layer		= Layer::Player;
	m_strName	= L"커비";

	m_pIdleLImage   = nullptr;
	m_pIdleRImage   = nullptr;
	m_pMoveLImage   = nullptr;
	m_pMoveRImage   = nullptr;
	m_pRunImage     = nullptr;
	m_pDownImage    = nullptr;
	m_pFlyImage	    = nullptr;
	m_pFlyingImage  = nullptr;
	m_pJumpImage	= nullptr;
	m_pJumpingImage = nullptr;
	m_groundchecker = false;
	m_vecMoveDir	= Vector(1, 0);
	m_vecLookDir	= Vector(0, 0);

	lastLeftInputTime  = 10;
	lastRightInputTime = 10;	
	fallTimer		   = 0;
	flyTimer		   = 0;
	m_groundCounter	   = 0;
	m_gravity		   = 300;
}

CKirby::~CKirby()
{

}

void CKirby::Init()
{
	m_pIdleLImage	= RESOURCE->LoadImg(L"KirbyIdleL",	L"Image\\Kirby\\Basic\\KirbyIdleL.png"	);
	m_pIdleRImage	= RESOURCE->LoadImg(L"KirbyIdleR",	L"Image\\Kirby\\Basic\\KirbyIdleR.png"	);
	m_pMoveLImage	= RESOURCE->LoadImg(L"KirbyLW",		L"Image\\Kirby\\Basic\\KirbyLW.png"		);
	m_pMoveRImage	= RESOURCE->LoadImg(L"KirbyRW",		L"Image\\Kirby\\Basic\\KirbyRW.png"		);
	m_pRunImage		= RESOURCE->LoadImg(L"KirbyRun",	L"Image\\Kirby\\Basic\\KirbyRun.png"	);
	m_pDownImage	= RESOURCE->LoadImg(L"KirbyDown",	L"Image\\Kirby\\Basic\\KirbyDown.png"	);
	m_pFlyImage		= RESOURCE->LoadImg(L"KirbyFly",	L"Image\\Kirby\\Basic\\KirbyFly.png"	);
	m_pFlyingImage  = RESOURCE->LoadImg(L"KirbyFly",	L"Image\\Kirby\\Basic\\KirbyFly.png"	);
	m_pJumpImage    = RESOURCE->LoadImg(L"KirbyJump",	L"Image\\Kirby\\Basic\\KirbyJump.png"	);

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

	m_pAnimator->Play(L"IdleR", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Circle, Vector(20, 20), Vector(0, 0));
}


void CKirby::Update()
{
	m_jumpSpeed -= m_gravity * DT;
	fallTimer += DT;
	lastLeftInputTime += DT;
	lastRightInputTime += DT;
	m_vecLookDir = m_vecMoveDir;
	Logger::Debug(to_wstring(m_groundCounter));

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

void CKirby::Render()
{
}

void CKirby::AnimatorUpdate()
{
	m_pAnimator->Play(kirbystate, false);
}



void CKirby::Jump()
{
	m_jumpSpeed = 300;
	fallTimer = 0;
}

void CKirby::IdleState()
{
	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * DT;
	}
	if (m_vecLookDir.x == -1)
	{
		kirbystate = L"IdleL";
	}
	else if (m_vecLookDir.x == 1)
	{
		kirbystate = L"IdleR";
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

void CKirby::WalkState()
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
		kirbystate = L"LW";
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		m_vecMoveDir.x = 1;
		m_vecPos.x += m_fSpeed * DT;
		kirbystate = L"RW";
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

void CKirby::RunState()
{
	m_fSpeed = 200.0f;
	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * DT;
	}
	if (BUTTONSTAY(VK_LEFT))
	{
		m_vecMoveDir.x = -1;
		kirbystate = L"LRun";
		m_vecPos.x -= m_fSpeed * DT;
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		m_vecMoveDir.x = 1;
		kirbystate = L"RRun";
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

void CKirby::JumpState() 
{
	m_vecPos.y -= m_jumpSpeed * DT;

	if (m_vecLookDir.x == -1)
	{
		kirbystate = L"LJump";
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
		kirbystate = L"RJump";
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

void CKirby::SitState()
{
	if (m_vecLookDir.x == 1)
	{
		kirbystate = L"RDown";
		if (BUTTONSTAY(VK_DOWN) && BUTTONSTAY(VK_LEFT))
		{
			m_vecLookDir.x = -1;
			kirbystate = L"LDown";
		}
	}
	else if (m_vecLookDir.x == -1)
	{
		kirbystate = L"LDown";
		if (BUTTONSTAY(VK_DOWN) && BUTTONDOWN(VK_LEFT))
		{
			m_vecLookDir.x = 1;
			kirbystate = L"RDown";
		}
	}
	if (!BUTTONSTAY(VK_DOWN))
	m_state = State::Idle;
}

void CKirby::FlyState()
{
	flyTimer += DT;
	//땅에있고  && 0.5초동안 플라이
	m_fSpeed = 100;
	if (m_vecLookDir.x == 1)
	{
		kirbystate = L"RFly";
		if (flyTimer > 0.4f)
		{ 
			flyTimer = 0;
			m_state = State::Flying;
		}
	}
	else if (m_vecLookDir.x == -1)
	{
		kirbystate = L"LFly";
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

void CKirby::AttackState()
{
	CreateMissile();
	m_state = State::Idle;
}

void CKirby::JumpingDownState()
{
	m_vecPos.y -= m_jumpSpeed * DT;
	if (m_vecLookDir.x == -1)
	{
		kirbystate = L"LJumping";
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
		kirbystate = L"RJumping";
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

void CKirby::FlyingState()
{
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
		kirbystate = L"RFlying";
	}
	else if (m_vecLookDir.x == -1)
	{
		kirbystate = L"LFlying";
	}
	
	if(BUTTONUP(VK_UP))
	{
		m_jumpSpeed = 0;
		m_state = State::JumpingDown;
	}

	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * 0.1f * DT;
	}

	m_groundchecker = false;

}


void CKirby::Release()
{

}

void CKirby::CreateMissile()
{
	Logger::Debug(L"미사일 생성");

	CMissile* pMissile = new CMissile();
	pMissile->SetPos(m_vecPos);
	pMissile->SetDir(Vector(1, 0));
	ADDOBJECT(pMissile);

	CMissile* pMissile1 = new CMissile();
	pMissile1->SetPos(m_vecPos);
	pMissile1->SetDir(Vector(1, -1));
	ADDOBJECT(pMissile1);

	CMissile* pMissile2 = new CMissile();
	pMissile2->SetPos(m_vecPos);
	pMissile2->SetDir(Vector(1, 1));
	ADDOBJECT(pMissile2);

	CMissile* pMissile3 = new CMissile();
	pMissile3->SetPos(m_vecPos);
	pMissile3->SetDir(Vector(3, 1));
	ADDOBJECT(pMissile3);

	CMissile* pMissile4 = new CMissile();
	pMissile4->SetPos(m_vecPos);
	pMissile4->SetDir(Vector(3, -1));
	ADDOBJECT(pMissile4);
}

void CKirby::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"바닥")
	{
		m_groundCounter++;
		m_groundchecker = true;
	}

}


void CKirby::OnCollisionStay(CCollider* pOtherCollider)
{

}

void CKirby::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"바닥")
	{
		--m_groundCounter;
		if (m_groundCounter <= 0)
		{
			m_groundchecker = false;
		}
	}
}