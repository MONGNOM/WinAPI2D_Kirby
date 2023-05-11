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

	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
}

CKirby::~CKirby()
{
}

void CKirby::Init()
{
	m_pIdleLImage = RESOURCE->LoadImg(L"KirbyIdleL", L"Image\\Kirby\\Basic\\KirbyIdleL.png");
	m_pIdleRImage = RESOURCE->LoadImg(L"KirbyIdleR", L"Image\\Kirby\\Basic\\KirbyIdleR.png");
	m_pMoveLImage = RESOURCE->LoadImg(L"KirbyLW", L"Image\\Kirby\\Basic\\KirbyLW.png");
	m_pMoveRImage = RESOURCE->LoadImg(L"KirbyRW", L"Image\\Kirby\\Basic\\KirbyRW.png");
	m_pRunImage = RESOURCE->LoadImg(L"KirbyRun", L"Image\\Kirby\\Basic\\KirbyRun.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IdleR", m_pIdleRImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"IdleL", m_pIdleLImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"LW", m_pMoveLImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"RW", m_pMoveRImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"LRun", m_pRunImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"RRun", m_pRunImage, Vector(490.f, 104.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 8);

	m_pAnimator->Play(L"IdleR", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(90, 90), Vector(0, 0));
}

void CKirby::Update()
{

	switch (m_state)
	{
		m_vecLookDir = m_vecMoveDir;
	case state::Idle:
		if (m_vecLookDir.x = -1)
		{
			kirbystate = L"IdleL";
		}
		else if (m_vecLookDir.x = 1)
		{
			kirbystate = L"IdleR";
		}

		if (BUTTONDOWN(VK_LEFT) || BUTTONDOWN(VK_RIGHT))
		{
			m_state = state::Walk;
		}

		break;
	case state::Walk:
		m_fSpeed = 100.f;

		if (BUTTONSTAY(VK_LEFT))
		{
			m_vecMoveDir.x = -1;
			m_vecPos.x -= m_fSpeed * DT;
			kirbystate = L"LW";
			runTimer += DT;
			if (runTimer <= 1)
			{
				if (BUTTONSTAY(VK_LEFT))
				{
					m_state = state::Run;
				}
			}
		}
		else if (BUTTONSTAY(VK_RIGHT))
		{
			m_vecMoveDir.x = 1;
			m_vecPos.x += m_fSpeed * DT;
			kirbystate = L"RW";
			runTimer += DT;
			if (runTimer <= 1)
			{
				if (BUTTONSTAY(VK_RIGHT))
				{
					m_state = state::Run;
				}
			}
		}
		else
		{
			m_vecMoveDir.x = 0;
		}

		if (!(BUTTONSTAY(VK_RIGHT) || BUTTONSTAY(VK_LEFT)))
		{
			m_state = state::Idle;
		}
		break;
	case state::Run:
		m_fSpeed = 200.0f;
		if (BUTTONSTAY(VK_LEFT))
		{
			kirbystate = L"LRun";
			m_vecMoveDir.x = -1;

		}
		else if (BUTTONSTAY(VK_RIGHT))
		{
			m_vecMoveDir.x = 1;
			kirbystate = L"RRun";
		}
		if (!(BUTTONSTAY(VK_RIGHT) || BUTTONSTAY(VK_LEFT)))
		{
			m_state = state::Idle;
		}
		break;
	case state::Jump:

		break;
	case state::Sit:

		break;
	case state::Fly:

		break;

	case state::Attack:

		break;
	default:
		break;
	}


	if (BUTTONDOWN(VK_SPACE))
	{
		CreateMissile();
	}

	AnimatorUpdate();
}

void CKirby::Render()
{
}

void CKirby::Release()
{
}

void CKirby::AnimatorUpdate()
{
	m_pAnimator->Play(kirbystate, false);
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