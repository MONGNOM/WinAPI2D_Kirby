#include "framework.h"
#include "CIceMonster.h"
#include "WinAPI.h"
#include "CCollider.h"
#include "CTimeManager.h"
#include "CImage.h"
#include "CAnimator.h"
#include "CEventManager.h"
#include "CRenderManager.h"


CIceMonster::CIceMonster()
{
	m_vecLookDir = Vector(-1, 0);
	m_state = State::Walk;
	m_pAnimator = nullptr;
	m_pMoveImage = nullptr;
	m_pDieImage = nullptr;
	m_pAttackImage = nullptr;
	hp = 2;
}

CIceMonster::~CIceMonster()
{
}


void CIceMonster::Init()
{
	m_pMoveImage	= RESOURCE->LoadImg(L"IceMonsterMove", L"Image\\Monster\\IceMonster\\IceMonsterWalk.png");
	m_pDieImage		= RESOURCE->LoadImg(L"IceMonsterDie", L"Image\\Monster\\IceMonster\\IceMonsterDie.png");
	m_pAttackImage	= RESOURCE->LoadImg(L"IceMonsterAttack", L"Image\\Monster\\IceMonster\\IceMonsterAttackPose.png");


	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"WalkR", m_pMoveImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.15f, 3);
	m_pAnimator->CreateAnimation(L"WalkL", m_pMoveImage, Vector(145.f, 100.f), Vector(50.f, 58.f), Vector(-70.f, 0.f), 0.15f, 3);	
	m_pAnimator->CreateAnimation(L"DieR", m_pDieImage, Vector(0.f, 0.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"DieL", m_pDieImage, Vector(0.f, 100.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"DizzyR", m_pDieImage, Vector(0.f, 0.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 1);
	m_pAnimator->CreateAnimation(L"DizzyL", m_pDieImage, Vector(0.f, 100.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 1);
	m_pAnimator->CreateAnimation(L"AttackR", m_pAttackImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.15f, 6);
	m_pAnimator->CreateAnimation(L"AttackL", m_pAttackImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.15f, 6);

	m_pAnimator->Play(L"WalkR", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Circle, Vector(20, 20), Vector(0, 0));

}

void CIceMonster::Update()
{
	

	CMonster::Update();
	switch (m_state)
	{
	case CIceMonster::State::Walk:
		WalkState();
		break;
	case CIceMonster::State::Die:
		DieState();
		break;
	case CIceMonster::State::Attack:
		AttackState();
		break;
	case State::Dizzy:
		DizzyState();
	default:
		break;
	}

	AnimatorUpdate();
}

void CIceMonster::Render()
{
}

void CIceMonster::Release()
{
}



void CIceMonster::WalkState()
{
	if (m_vecLookDir.x == 1)
	{
		iceState = L"WalkR";
		m_vecPos.x += 50 * DT;

	}
	if (m_vecLookDir.x == -1)
	{
		iceState = L"WalkL";
		m_vecPos.x -= 50 * DT;

	}
	if (dizzy)
	{
		m_state = State::Dizzy;
	}
	if (hp <= 0)
	{
		m_state = State::Die;
	}
}

void CIceMonster::DieState()
{
	dieTime += DT;
		if (m_vecLookDir.x == 1)
		{
			iceState = L"DieR";
			if (dieTime > 1.f)
			{
				dieTime = 0;
				DELETEOBJECT(this);
			}
		}
		if (m_vecLookDir.x == -1)
		{
			iceState = L"DieL";
			if (dieTime > 1.f)
			{
				dieTime = 0;
				DELETEOBJECT(this);
			}
		}
	
}

void CIceMonster::AttackState()
{
}

void CIceMonster::DizzyState()
{
	dieTime += DT;
	if (m_vecLookDir.x == 1)
	{
		iceState = L"DizzyR";
		if (dieTime > 0.5f)
		{
			dieTime = 0;
			m_state = State::Walk;
		}
	}
	if (m_vecLookDir.x == -1)
	{
		iceState = L"DizzyL";
		if (dieTime > 0.5f)
		{
			dieTime = 0;
			m_state = State::Walk;
		}
	}
}

void CIceMonster::AnimatorUpdate()
{
	m_pAnimator->Play(iceState, false);
}
