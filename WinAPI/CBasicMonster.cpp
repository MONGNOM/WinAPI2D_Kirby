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
	m_pIceDieImage = nullptr;

	hp = 2;
}

CBasicMonster::~CBasicMonster()
{
}


void CBasicMonster::Init()
{
	CMonster::Init();

	m_pMoveImage	= RESOURCE->LoadImg(L"BasicMonsterWalk",	L"Image\\Monster\\BasicMonster\\BasicMonster.png");
	m_pDieImage		= RESOURCE->LoadImg(L"BasicMonsterDie",		L"Image\\Monster\\BasicMonster\\BasicMonsterDie.png");
	m_pIceDieImage = RESOURCE->LoadImg(L"IceDie", L"Image\\MonstericeStatesmall.png");



	m_pAnimator	= new CAnimator;
	m_pAnimator->CreateAnimation(L"WalkR",	m_pMoveImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.15f, 6);
	m_pAnimator->CreateAnimation(L"WalkL",	m_pMoveImage, Vector(0.f, 100.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.15f, 6);
	m_pAnimator->CreateAnimation(L"DieR",	m_pDieImage, Vector(0.f, 0.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"DieL", m_pDieImage, Vector(0.f, 100.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"DizzyR", m_pDieImage, Vector(0.f, 0.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 1);
	m_pAnimator->CreateAnimation(L"DizzyL",	m_pDieImage, Vector(0.f, 100.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 1);
	m_pAnimator->CreateAnimation(L"IceDie", m_pIceDieImage, Vector(0.f, 0.f), Vector(55.f, 57.f), Vector(0.f, 0.f), 0.5f, 1);


	m_pAnimator->Play(L"WalkR", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Circle, Vector(20, 20), Vector(0, 0));
}

void CBasicMonster::AnimatorUpdate()
{
	m_pAnimator->Play(Basicstate, false);
}

void CBasicMonster::Update()
{
	CMonster::Update();
	collider->SetPos(m_vecPos);


	switch(m_state)
	{
	case State::Walk:
		WalkState();
		break;
	case State::Die:
		DieState();
		break;
	case State::Dizzy:
		DizzyState();
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
	if (dizzy)
	{
		m_state = State::Dizzy;
		dizzy = false;
	}
	if (hp <= 0)
	{
		SOUND->Play(DeathSound, 0.1f, false);
		m_state = State::Die;
	}
}

void CBasicMonster::DieState()
{
	dieTimer += DT;
	if (iceDie)
	{
		if (m_vecLookDir.x == 1)
		{
			Basicstate = L"IceDie";
			if (dieTimer > 1.f)
			{
				dieTimer = 0;
				DELETEOBJECT(this); DELETEOBJECT(collider);
			}
		}
		if (m_vecLookDir.x == -1)
		{
			Basicstate = L"IceDie";
			if (dieTimer > 1.f)
			{
				dieTimer = 0;
				DELETEOBJECT(this); DELETEOBJECT(collider);
			}
		}
	}
	else
	{
		if (m_vecLookDir.x == 1)
		{
			Basicstate = L"DieR";
			if (dieTimer > 1.f)
			{
				dieTimer = 0;
				DELETEOBJECT(this); DELETEOBJECT(collider);
			}
		}
		if (m_vecLookDir.x == -1)
		{
			Basicstate = L"DieL";
			if (dieTimer > 1.f)
			{
				dieTimer = 0;
				DELETEOBJECT(this); DELETEOBJECT(collider);
			}
		}
	}
}

void CBasicMonster::DizzyState()
{
	dieTimer += DT;
	if (m_vecLookDir.x == 1)
	{
		Basicstate = L"DizzyR";
		if (dieTimer > 0.5f)
		{
			dieTimer = 0;
			m_state = State::Walk;
		}
	}
	if (m_vecLookDir.x == -1)
	{
		Basicstate = L"DizzyL";
		if (dieTimer > 0.5f)
		{
			dieTimer = 0;
			m_state = State::Walk;
		}
	}
}

void CBasicMonster::Render()
{
}

void CBasicMonster::Release()
{
}

