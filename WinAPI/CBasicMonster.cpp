#include "framework.h"
#include "CBasicMonster.h"
#include "WinAPI.h"

#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"
#include "CEventManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"




CBasicMonster::CBasicMonster()
{
	m_state = State::Walk;
	m_pMoveImage = nullptr;
	m_pDieImage = nullptr;
	m_pAnimator = nullptr;
	hp = 1;
}

CBasicMonster::~CBasicMonster()
{
}


void CBasicMonster::Init()
{
	m_pMoveImage	= RESOURCE->LoadImg(L"BasicMonsterWalk",	L"Image\\Monster\\BasicMonster\\BasicMonster.png");
	m_pDieImage		= RESOURCE->LoadImg(L"BasicMonsterDie",		L"Image\\Monster\\BasicMonster\\BasicMonsterDie.png");

	m_pAnimator	= new CAnimator;
	m_pAnimator->CreateAnimation(L"WalkR",	m_pMoveImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.15f, 6);
	m_pAnimator->CreateAnimation(L"WalkL",	m_pMoveImage, Vector(0.f, 100.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.15f, 6);
	m_pAnimator->CreateAnimation(L"DieR",	m_pDieImage, Vector(0.f, 0.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"DieL",	m_pDieImage, Vector(0.f, 100.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 2);


	m_pAnimator->Play(L"DieR", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Circle, Vector(20, 20), Vector(0, 0));
}

void CBasicMonster::AnimatorUpdate()
{
	m_pAnimator->Play(Basicstate, false);
}

void CBasicMonster::Update()
{
	Logger::Debug(wstring(Basicstate));
	switch(m_state)
	{
	case State::Walk:
		WalkState();
		break;
	case State::Die:
		DieState();
		break;
	default:
		break;
	}


	AnimatorUpdate();
}

void CBasicMonster::WalkState()
{
	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * DT;
	}
	if (m_vecLookDir.x == 1 && hp > 0)
	{
		Basicstate = L"WalkR";
		m_vecPos.x += 50 * DT;
	}
	if (m_vecLookDir.x == -1 && hp > 0)
	{
		Basicstate = L"WalkL";
		m_vecPos.x -= 50 * DT;
	}
	if (hp == 0)
	{
		m_state = State::Die;
	}
}

void CBasicMonster::DieState()
{
	dieTime += DT;
	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * DT;
	}
	if (m_vecLookDir.x == 1)
	{
		Basicstate = L"DieR";
		if (dieTime > 1.f)
		{
			dieTime = 0;
			DELETEOBJECT(this);
		}
	}
	if (m_vecLookDir.x == -1)
	{
		Basicstate = L"DieL";
		if (dieTime > 1.f)
		{
			dieTime = 0;
			DELETEOBJECT(this);
		}
	}
}

void CBasicMonster::Render()
{
}

void CBasicMonster::Release()
{
}

