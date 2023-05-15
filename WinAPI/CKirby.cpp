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
	runTimer = 0.f;
	m_fSpeed = 0.f;

	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Player;
	m_strName = L"플레이어";

	m_pIdleLImage  = nullptr;
	m_pIdleRImage  = nullptr;
	m_pMoveLImage  = nullptr;
	m_pMoveRImage  = nullptr;
	m_pRunImage    = nullptr;
	m_pDownImage   = nullptr;
	m_pFlyImage	   = nullptr;
	m_pFlyingImage = nullptr;

	m_vecMoveDir = Vector(1, 0);
	m_vecLookDir = Vector(0, 0);

	lastLeftInputTime = 10;
	lastRightInputTime = 10;
}

CKirby::~CKirby()
{
}

void CKirby::Init()
{
	m_pIdleLImage	= RESOURCE->LoadImg(L"KirbyIdleL", L"Image\\Kirby\\Basic\\KirbyIdleL.png");
	m_pIdleRImage	= RESOURCE->LoadImg(L"KirbyIdleR", L"Image\\Kirby\\Basic\\KirbyIdleR.png");
	m_pMoveLImage	= RESOURCE->LoadImg(L"KirbyLW", L"Image\\Kirby\\Basic\\KirbyLW.png");
	m_pMoveRImage	= RESOURCE->LoadImg(L"KirbyRW", L"Image\\Kirby\\Basic\\KirbyRW.png");
	m_pRunImage		= RESOURCE->LoadImg(L"KirbyRun", L"Image\\Kirby\\Basic\\KirbyRun.png");
	m_pDownImage	= RESOURCE->LoadImg(L"KirbyDown", L"Image\\Kirby\\Basic\\KirbyDown.png");
	m_pFlyImage		= RESOURCE->LoadImg(L"KirbyFly", L"Image\\Kirby\\Basic\\KirbyFly.png");
	m_pFlyingImage	= RESOURCE->LoadImg(L"KirbyFly", L"Image\\Kirby\\Basic\\KirbyFly.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IdleR", m_pIdleRImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"IdleL", m_pIdleLImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"LW", m_pMoveLImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"RW", m_pMoveRImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"RRun", m_pRunImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"LRun", m_pRunImage, Vector(490.f, 104.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"LDown", m_pDownImage, Vector(0.f, 100.f), Vector(50.f, 50.f), Vector(50.f, 0.f), 10.0f, 1);
	m_pAnimator->CreateAnimation(L"RDown", m_pDownImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(50.f, 0.f), 10.0f, 1);


	m_pAnimator->CreateAnimation(L"RFlying", m_pFlyImage, Vector(400.f, 0.f), Vector(85.f, 50.f), Vector(70.f, 0.f), 0.08f, 6);
	m_pAnimator->CreateAnimation(L"LFlying", m_pFlyImage, Vector(400.f, 100.f), Vector(85.f, 50.f), Vector(70.f, 0.f), 0.08f, 6);
	m_pAnimator->CreateAnimation(L"RFly", m_pFlyImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 19, false);
	m_pAnimator->CreateAnimation(L"LFly", m_pFlyImage, Vector(0.f, 100.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 19, false);
	m_pAnimator->Play(L"IdleR", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(90, 90), Vector(0, 0));
}


void CKirby::Update()
{
	lastLeftInputTime += DT;
	lastRightInputTime += DT;
	m_vecLookDir = m_vecMoveDir;
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


void CKirby::IdleState()
{
	if (m_vecLookDir.x == -1)
	{
		kirbystate = L"IdleL";
	}
	else if (m_vecLookDir.x == 1)
	{
		kirbystate = L"IdleR";
	}
	if (BUTTONDOWN(VK_LEFT))
	{
		if (lastLeftInputTime < TIME_DASHABLE)
			m_state = State::Run;
		else
			m_state = State::Walk;

		lastLeftInputTime = 0;
	}
	if (BUTTONDOWN(VK_RIGHT))
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
	if (BUTTONSTAY('A'))
	{
		m_state = State::Jump;
	}
}

void CKirby::WalkState()
{
	m_fSpeed = 100.f;

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
	if (BUTTONSTAY('A'))
	{
		m_state = State::Jump;
	}
}

void CKirby::RunState()
{
	m_fSpeed = 200.0f;
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
	if (BUTTONSTAY('A'))
	{
		m_state = State::Jump;
	}
}

void CKirby::JumpState()
{

}

void CKirby::SitState()
{
	if (m_vecLookDir.x == 1) kirbystate = L"RDown";
	else kirbystate = L"LDown";

	if (!BUTTONSTAY(VK_DOWN))
	m_state = State::Idle;
}

void CKirby::FlyState()
{
	// fly도중 방향전환 코드 수정 + 땅에있고  && 0.5초동안 플라이 && UP만 눌렀을때 하늘로만 가고 방향키 누르면 방향키로 이동하게 수정
	if (BUTTONSTAY(VK_UP) && m_vecLookDir.x == 1)
	{
		m_vecPos.y -= m_fSpeed * DT;
		kirbystate = L"RFly";
		if (BUTTONSTAY(VK_RIGHT))
		{
			m_vecPos.y -= m_fSpeed * DT;
			m_vecPos.x += m_fSpeed * DT;
			kirbystate = L"RFly";

		}
		else if (BUTTONSTAY(VK_LEFT))
		{
			m_vecPos.y -= m_fSpeed * DT;
			m_vecPos.x -= m_fSpeed * DT;
			kirbystate = L"LFly";
		}
	}
	else if (BUTTONSTAY(VK_UP) && m_vecLookDir.x == -1)
	{
		m_vecPos.y -= m_fSpeed * DT;
		kirbystate = L"LFly";
		if (BUTTONSTAY(VK_RIGHT))
		{
			m_vecPos.y -= m_fSpeed * DT;
			m_vecPos.x += m_fSpeed * DT;
			kirbystate = L"RFly";

		}
		else if (BUTTONSTAY(VK_LEFT))
		{
			m_vecPos.y -= m_fSpeed * DT;
			m_vecPos.x -= m_fSpeed * DT;
			kirbystate = L"LFly";
		}
	}
	else
	{
		m_vecPos = Vector(600, 500);
		m_state = State::Idle;
	}

	/* 날고있는 상태 애니메이션 구현중
	if (BUTTONSTAY(VK_UP) && m_vecLookDir.x == 1)
	{
		m_vecLookDir.x = 1;
		kirbystate = L"RFlying";
	}
	else if (BUTTONSTAY(VK_UP) && m_vecLookDir.x == -1)
	{
		m_vecLookDir.x = -1;
		kirbystate = L"LFlying";
	}
	else m_state = State::Idle;
	*/
	if (BUTTONDOWN('A'))
	{
		m_state = State::Attack;
	}

}

void CKirby::AttackState()
{
	CreateMissile();
	m_state = State::Idle;
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
}

void CKirby::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CKirby::OnCollisionExit(CCollider* pOtherCollider)
{
}