#include "framework.h"
#include "CIceMonster.h"
#include "WinAPI.h"
#include "CCollider.h"
#include "CTimeManager.h"
#include "CImage.h"
#include "CAnimator.h"
#include "CEventManager.h"
#include "CRenderManager.h"
#include "CKirbyWeapon.h"


CIceMonster::CIceMonster()
{
	m_vecLookDir = Vector(-1, 0);
	m_state = State::Walk;
	m_pAnimator = nullptr;
	m_pMoveImage = nullptr;
	m_pDieImage = nullptr;
	m_pAttackImage = nullptr;
	m_pIceDieImage = nullptr;
	hp = 2;
	m_strName = L"얼음몬스터";
}

CIceMonster::~CIceMonster()
{
}


void CIceMonster::Init()
{

	CMonster::Init();
	m_pMoveImage	= RESOURCE->LoadImg(L"IceMonsterMove", L"Image\\Monster\\IceMonster\\IceMonsterWalk.png");
	m_pDieImage		= RESOURCE->LoadImg(L"IceMonsterDie", L"Image\\Monster\\IceMonster\\IceMonsterDie.png");
	m_pAttackImage	= RESOURCE->LoadImg(L"IceMonsterAttack", L"Image\\Monster\\IceMonster\\IceMonsterAttackPose.png");

	m_pIceDieImage	= RESOURCE->LoadImg(L"IceDie", L"Image\\MonstericeStatesmall.png");


	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"WalkR", m_pMoveImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.15f, 3);
	m_pAnimator->CreateAnimation(L"WalkL", m_pMoveImage, Vector(145.f, 100.f), Vector(50.f, 58.f), Vector(-70.f, 0.f), 0.15f, 3);	
	m_pAnimator->CreateAnimation(L"DieR", m_pDieImage, Vector(0.f, 0.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"DieL", m_pDieImage, Vector(0.f, 100.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"DizzyR", m_pDieImage, Vector(0.f, 0.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 1);
	m_pAnimator->CreateAnimation(L"DizzyL", m_pDieImage, Vector(0.f, 100.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 1);
	m_pAnimator->CreateAnimation(L"AttackR", m_pAttackImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.15f, 6);
	m_pAnimator->CreateAnimation(L"AttackL", m_pAttackImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.15f, 6);

	m_pAnimator->CreateAnimation(L"IceDie", m_pIceDieImage, Vector(0.f, 0.f), Vector(54.f, 57.f), Vector(0.f, 0.f), 0.5f, 1);


	m_pAnimator->Play(L"WalkR", false);
	AddComponent(m_pAnimator);
	collider->SetColliderScale(200, 100);

	AddCollider(ColliderType::Circle, Vector(20, 20), Vector(0, 0));

}

void CIceMonster::Update()
{
	CMonster::Update();
	collider->SetPos(m_vecPos);

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
	dieTimer += DT;
	if (iceDie)
	{
		if (m_vecLookDir.x == 1)
		{
			iceState = L"IceDie";
			if (dieTimer > 1.f)
			{
				dieTimer = 0;
				DELETEOBJECT(this); DELETEOBJECT(collider);
			}
		}
		if (m_vecLookDir.x == -1)
		{
			iceState = L"IceDie";
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
			iceState = L"DieR";
			if (dieTimer > 1.f)
			{
				dieTimer = 0;
				DELETEOBJECT(this); DELETEOBJECT(collider);
			}
		}
		if (m_vecLookDir.x == -1)
		{
			iceState = L"DieL";
			if (dieTimer > 1.f)
			{
				dieTimer = 0;
				DELETEOBJECT(this); DELETEOBJECT(collider);
			}
		}
	}
	
}

void CIceMonster::AttackState()
{
}

void CIceMonster::DizzyState()
{
	dieTimer += DT;
	if (m_vecLookDir.x == 1)
	{
		iceState = L"DizzyR";
		if (dieTimer > 0.5f)
		{
			dieTimer = 0;
			m_state = State::Walk;
		}
	}
	if (m_vecLookDir.x == -1)
	{
		iceState = L"DizzyL";
		if (dieTimer > 0.5f)
		{
			dieTimer = 0;
			m_state = State::Walk;
		}
	}
}



void CIceMonster::AnimatorUpdate()
{
	m_pAnimator->Play(iceState, false);
}
