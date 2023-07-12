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
#include "CKirbyEat.h"
#include "CKirbyShot.h"
#include "CIceKirby.h"
#include "CSwordKirby.h"
#include "CGameManager.h"




CNomalKirby::CNomalKirby()
{
	m_state				= State::Idle;
	m_pAnimator			= nullptr;
	m_pIdleLImage		= nullptr;
	m_pIdleRImage		= nullptr;
	m_pMoveLImage		= nullptr;
	m_pMoveRImage		= nullptr;
	m_pRunImage			= nullptr;
	m_pDownImage		= nullptr;
	m_pFlyImage			= nullptr;
	m_pJumpImage		= nullptr;
	m_pJumpingImage		= nullptr;
	m_pAttackImage		= nullptr;
	m_pKirbyEat			= nullptr;
	m_pEatWalkImage		= nullptr;
	m_pEatChangeImage	= nullptr;
	m_pEatAttackImage	= nullptr;
	eating				= false;
	eat					= false;
	swordicon			= false;
	iceicon				= false;
	ice					= GAME->ice;
	sword				= GAME->sword;
	iceicon				= GAME->iceicon;
	swordicon			= GAME->swordicon;
	attackTimer			= 0;
	changeTimer			= 0;
	m_strName			= L"일반커비";
}

CNomalKirby::~CNomalKirby()
{

}



void CNomalKirby::Init()
{
	
	CKirby::Init();

	m_pIdleLImage		= RESOURCE->LoadImg(L"KirbyIdleL",		L"Image\\Kirby\\Basic\\KirbyIdleL.png"	);
	m_pIdleRImage		= RESOURCE->LoadImg(L"KirbyIdleR",		L"Image\\Kirby\\Basic\\KirbyIdleR.png"	);
	m_pMoveLImage		= RESOURCE->LoadImg(L"KirbyLW",			L"Image\\Kirby\\Basic\\KirbyLW.png"		);
	m_pMoveRImage		= RESOURCE->LoadImg(L"KirbyRW",			L"Image\\Kirby\\Basic\\KirbyRW.png"		);
	m_pRunImage			= RESOURCE->LoadImg(L"KirbyRun",		L"Image\\Kirby\\Basic\\KirbyRun.png"	);
	m_pDownImage		= RESOURCE->LoadImg(L"KirbyDown",		L"Image\\Kirby\\Basic\\KirbyDown.png"	);
	m_pFlyImage			= RESOURCE->LoadImg(L"KirbyFly",		L"Image\\Kirby\\Basic\\KirbyFly.png"	);
	m_pJumpImage		= RESOURCE->LoadImg(L"KirbyJump",		L"Image\\Kirby\\Basic\\KirbyJump.png"	);
	m_pAttackImage		= RESOURCE->LoadImg(L"KirbyAttack",		L"Image\\Kirby\\Basic\\KirbyEat.png"	);
	m_pEatWalkImage		= RESOURCE->LoadImg(L"KirbyEatWalk",	L"Image\\Kirby\\Basic\\KirbyEatRun.png"	);
	m_pEatChangeImage	= RESOURCE->LoadImg(L"KirbyEatChange",	L"Image\\Kirby\\Basic\\KirbyDiner.png"	);
	m_pEatAttackImage	= RESOURCE->LoadImg(L"KirbyEatAttack",	L"Image\\Kirby\\Basic\\KirbyNotEat.png"	);

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Disappear",	m_pMoveLImage, Vector(0.f, 0.f), Vector(1.f, 1.f), Vector(1.f, 0.f), 0.f, 1);
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


	//Eat
	m_pAnimator->CreateAnimation(L"EatIdleR",	m_pEatChangeImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(0.f, 0.f), 0.f, 1);
	m_pAnimator->CreateAnimation(L"EatIdleL",	m_pEatChangeImage, Vector(0.f, 100.f), Vector(50.f, 50.f), Vector(0.f, 0.f), 0.f, 1);
	m_pAnimator->CreateAnimation(L"EatLW",		m_pEatWalkImage,	Vector(60.f, 100.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 15);
	m_pAnimator->CreateAnimation(L"EatRW",		m_pEatWalkImage,	Vector(70.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 15);
	m_pAnimator->CreateAnimation(L"EatAttackR", m_pEatAttackImage, Vector(0.f, 0.f), Vector(57.f, 57.f), Vector(70.f, 0.f), 0.08f, 5);
	m_pAnimator->CreateAnimation(L"EatAttackL", m_pEatAttackImage, Vector(0.f, 95.f), Vector(57.f, 57.f), Vector(70.f, 0.f), 0.08f, 5);
	m_pAnimator->CreateAnimation(L"EatChangeR", m_pEatChangeImage, Vector(0.f, 0.f), Vector(57.f, 57.f), Vector(70.f, 0.f), 0.04f, 9);
	m_pAnimator->CreateAnimation(L"EatChangeL", m_pEatChangeImage, Vector(0.f, 95.f), Vector(57.f, 57.f), Vector(70.f, 0.f), 0.04f, 9);
	m_pAnimator->Play(L"EatIdleR", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(40, 40), Vector(0, 0));
	ChangeSound = RESOURCE->LoadSound(L"ChangeSound", L"Sound\\Change.wav");
	NotChangeSound = RESOURCE->LoadSound(L"NotChangeSound", L"Sound\\NormalChange.wav");
	EattingSound = RESOURCE->LoadSound(L"EattingSound", L"Sound\\EattingSound.wav");
	EatSound = RESOURCE->LoadSound(L"EatSound", L"Sound\\Eat.wav");
	ShotSound = RESOURCE->LoadSound(L"ShotSound", L"Sound\\Shot.wav");
}


void CNomalKirby::Update()
{
	GAME->ice = ice;
	GAME->sword = sword;
	GAME->iceicon = iceicon;
	GAME->swordicon = swordicon;

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
	case State::Change:
		ChangeState();
		break;
	case State::Eating:
		EatingState();
		break;
	case State::EatWalk:
		EatWalkState();
		break;
	case State::EatAttack:
		EatAttackState();
		break;
	case State::Disappear:
		DisappearState();
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
	m_pAnimator->Play(normalkirbystate, false);
}


void CNomalKirby::DisappearState()
{

	if (ice)
	{
		GAME->iceicon = true;
	}
	if (sword)
	{
		GAME->swordicon = true;
	}
	changeTimer += DT;
	normalkirbystate = L"Disappear";
	if (changeTimer > 0.42f)
	{
		DELETEOBJECT(this);
		DELETEOBJECT(effect);
		changeTimer = 0;
	}
	
}

void CNomalKirby::Jump()
{
	m_jumpSpeed = 300;
	fallTimer = 0;
	SelectSound(JumpSound, 0.1f, false);
	
}

#pragma region 상태패턴함수


void CNomalKirby::IdleState()
{
	swordicon = false;
	iceicon = false;
	eat = false;
	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * DT;
	}
	if (m_vecLookDir.x == -1)
	{
		normalkirbystate = L"IdleL";
	}
	else if (m_vecLookDir.x == 1)
	{
		normalkirbystate = L"IdleR";
	}
	if (BUTTONSTAY(VK_LEFT))
	{
		if (lastLeftInputTime < TIME_DASHABLE)
		{
			SelectSound(RunSound, 0.1f, false);
			Effect(m_vecPos.x);
			effect->KirbyDashEffectL();
			m_state = State::Run;
		}
		else
			m_state = State::Walk;

		lastLeftInputTime = 0;
	}
	if (BUTTONSTAY(VK_RIGHT))
	{
		if (lastRightInputTime < TIME_DASHABLE)
		{	
			SelectSound(RunSound, 0.1f, false);
			Effect(m_vecPos.x);
			effect->KirbyDashEffectR();
			m_state = State::Run;
		}
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
		normalkirbystate = L"LW";
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		m_vecMoveDir.x = 1;
		m_vecPos.x += m_fSpeed * DT;
		normalkirbystate = L"RW";

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
		effect->SetPos(m_vecPos.x + 35, m_vecPos.y + 5);
		m_vecMoveDir.x = -1;
		normalkirbystate = L"LRun";
		m_vecPos.x -= m_fSpeed * DT;
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		effect->SetPos(m_vecPos.x - 35 ,m_vecPos.y + 5);
		m_vecMoveDir.x = 1;
		normalkirbystate = L"RRun";
		m_vecPos.x += m_fSpeed * DT;
	}
	if (!(BUTTONSTAY(VK_RIGHT) || BUTTONSTAY(VK_LEFT)))
	{
		DELETEOBJECT(effect);
		m_state = State::Idle;
	}
	if (BUTTONDOWN('S'))
	{
		DELETEOBJECT(effect);
		m_state = State::Attack;
	}
	if (BUTTONSTAY(VK_DOWN))
	{
		DELETEOBJECT(effect);
		m_state = State::Sit;
	}
	if (BUTTONSTAY(VK_UP))
	{
		DELETEOBJECT(effect);
		m_state = State::Fly;
	}
	if (BUTTONDOWN('A'))
	{
		DELETEOBJECT(effect);
		Jump();
		m_state = State::Jump;
	}
}

void CNomalKirby::JumpState() 
{
	if (JumpSound == nullptr)
	{
		SelectSound(JumpSound, 0.1f, false);
	}
	m_vecPos.y -= m_jumpSpeed * DT;
	
	if (m_vecLookDir.x == -1)
	{
		normalkirbystate = L"LJump";
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
		normalkirbystate = L"RJump";
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
		normalkirbystate = L"RDown";
		if (BUTTONSTAY(VK_DOWN) && BUTTONSTAY(VK_LEFT))
		{
			m_vecLookDir.x = -1;
			normalkirbystate = L"LDown";
		}
	}
	else if (m_vecLookDir.x == -1)
	{
		normalkirbystate = L"LDown";
		if (BUTTONSTAY(VK_DOWN) && BUTTONDOWN(VK_LEFT))
		{
			m_vecLookDir.x = 1;
			normalkirbystate = L"RDown";
		}
	}
	if (!BUTTONSTAY(VK_DOWN))
	m_state = State::Idle;
}

void CNomalKirby::FlyState()
{
	flyTimer += DT;
	m_fSpeed = 100;
	if (m_vecLookDir.x == 1)
	{
		normalkirbystate = L"RFly";
		if (flyTimer > 0.4f)
		{ 
			SelectSound(FlySound, 0.5f, true);
			flyTimer = 0;
			m_state = State::Flying;
		}
	}
	else if (m_vecLookDir.x == -1)
	{
		normalkirbystate = L"LFly";
		if (flyTimer > 0.4f)
		{
			SelectSound(FlySound, 0.5f, true);

			flyTimer = 0;
			m_state = State::Flying;

		}
	}
	else if(BUTTONUP(VK_UP))
	{

		m_jumpSpeed = 0;
		m_state = State::JumpingDown;
	}
	
}

void CNomalKirby::AttackState()
{
	if (m_pKirbyEat == nullptr)
		AttackCollider();

	if (m_vecLookDir.x == -1)
	{
		normalkirbystate = L"LAttack";
	}
	if (m_vecLookDir.x == 1)
	{
		normalkirbystate = L"RAttack";
	}
	if (BUTTONUP('S'))
	{
		if (m_pKirbyEat != nullptr)
		{
			DELETEOBJECT(m_pKirbyEat);
			m_pKirbyEat = nullptr;
		}
		{
			SOUND->Pause(EattingSound);
			m_state = State::Idle;
		}
	}
	if (eating)
	{
		eating = false;
		SOUND->Pause(EattingSound);
		m_state = State::Eating;
	}
}

void CNomalKirby::EatingState()
{
	if (m_pKirbyEat != nullptr)
	{
		DELETEOBJECT(m_pKirbyEat);
		m_pKirbyEat = nullptr;
		SOUND->Play(EatSound, 0.1f, false);

	}
	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * DT;
	}
	if (m_vecLookDir.x == -1)
	{
		normalkirbystate = L"EatIdleL";
	}
	else if (m_vecLookDir.x == 1)
	{
		normalkirbystate = L"EatIdleR";
	}
	if (BUTTONSTAY(VK_LEFT))
	{
		m_state = State::EatWalk;
	}
	if (BUTTONSTAY(VK_RIGHT))
	{
		m_state = State::EatWalk;
	}
	if (BUTTONDOWN('S'))
	{
		m_state = State::EatAttack;
	}
	if (BUTTONDOWN(VK_DOWN))
	{
		m_state = State::Change;
	}
}

void CNomalKirby::ChangeState()
{

	changeTimer += DT;
	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * DT;
	}
	if (m_vecLookDir.x == -1)
	{
		normalkirbystate = L"EatChangeL";
		if (changeTimer > 0.36f)
		{
			changeTimer = 0;
			if (ice && !sword)
			{
				Effect(m_vecPos.x);
				effect->kirbyChangeEffect();
				IceKirbyChange();
				m_state = State::Disappear;
			}
			else if (sword && !ice)
			{
				Effect(m_vecPos.x);
				effect->kirbyChangeEffect();
				SwordirbyChange();
				m_state = State::Disappear;

			}
			else
			{
				m_state = State::Idle;
				SOUND->Play(NotChangeSound, 0.1f, false);
			}
		}
	}
	else if (m_vecLookDir.x == 1)
	{
		normalkirbystate = L"EatChangeR";
		if (changeTimer > 0.36f)
		{
			changeTimer = 0;
			if (ice && !sword)
			{
				Effect(m_vecPos.x);
				effect->kirbyChangeEffect();
				IceKirbyChange();
				m_state = State::Disappear;
				 
			}
			else if (sword && !ice)
			{
				Effect(m_vecPos.x);
				effect->kirbyChangeEffect();
				SwordirbyChange();
				m_state = State::Disappear;
			}
			else
			{
				m_state = State::Idle;
				SOUND->Play(NotChangeSound, 0.1f, false);
			}
		}
	}
	
}

void CNomalKirby::EatWalkState()
{
	if (BUTTONSTAY(VK_LEFT))
	{
		m_vecMoveDir.x = -1;
		m_vecPos.x -= m_fSpeed * DT;
		normalkirbystate = L"EatLW";
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		m_vecMoveDir.x = 1;
		m_vecPos.x += m_fSpeed * DT;
		normalkirbystate = L"EatRW";
	}

	if (!(BUTTONSTAY(VK_RIGHT) || BUTTONSTAY(VK_LEFT)))
	{
		m_state = State::Eating;
	}
	if (BUTTONDOWN('S'))
	{
		m_state = State::EatAttack;
	}
	if (BUTTONSTAY(VK_DOWN))
	{
		m_state = State::Change;
	}
}

void CNomalKirby::EatAttackState()
{
	ice = false;
	sword = false;
	attackTimer += DT;
	eating = false;
	if (m_pKirbyShot == nullptr)
	{
		SOUND->Play(ShotSound, 0.1f, false);
		m_pKirbyShot = new CKirbyShot(m_vecLookDir);
		ADDOBJECT(m_pKirbyShot);
		m_pKirbyShot->SetPos(m_vecPos);
	}

	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * DT;
	}
	if (m_vecLookDir.x == -1)
	{
		normalkirbystate = L"EatAttackL";
		if (attackTimer > 0.2f)
		{
			m_pKirbyShot = nullptr;
			eating = false;
			m_state = State::Idle;
			attackTimer = 0;
		}
	}
	else if (m_vecLookDir.x == 1)
	{
		normalkirbystate = L"EatAttackR";
		if (attackTimer > 0.2f)
		{
			m_pKirbyShot = nullptr;
			eating = false;
			m_state = State::Idle;
			attackTimer = 0;
		}
	}
	

}

void CNomalKirby::AttackCollider()
{
	SOUND->Play(EattingSound, 0.1f, true);
	eat = true;
	m_pKirbyEat = new CKirbyEat();
	if (m_vecLookDir.x == -1)
	{
		m_pKirbyEat->SetPos(m_vecPos.x - 35, m_vecPos.y);
	}
	if (m_vecLookDir.x == 1)
	{
		m_pKirbyEat->SetPos(m_vecPos.x + 35, m_vecPos.y);
	}
	ADDOBJECT(m_pKirbyEat);
	

}



void CNomalKirby::JumpingDownState()
{
	m_vecPos.y -= m_jumpSpeed * DT;
	if (m_vecLookDir.x == -1)
	{
		normalkirbystate = L"LJumping";
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
		normalkirbystate = L"RJumping";
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
		normalkirbystate = L"RFlying";
	}
	else if (m_vecLookDir.x == -1)
	{
		normalkirbystate = L"LFlying";
	}
	
	if(BUTTONDOWN('S'))
	{
		SOUND->Pause(FlySound);
		m_jumpSpeed = 0;
		m_state = State::JumpingDown;
	}

	m_groundchecker = false;

}

#pragma endregion

void CNomalKirby::Release()
{

}

void CNomalKirby::IceKirbyChange()
{ 
	CAMERA->FadeIn(0.1f, 0.7f);
	SOUND->Play(ChangeSound, 0.1f, false);
	icekirby = new CIceKirby();
	icekirby->SetPos(m_vecPos);
	ADDOBJECT(icekirby);
	ice = true;
}

void CNomalKirby::SwordirbyChange()
{
	CAMERA->FadeIn(0.1f, 0.7f);
	SOUND->Play(ChangeSound, 0.1f, false);
	swordKriby = new CSwordKirby();
	swordKriby->SetPos(m_vecPos.x,m_vecPos.y -30);
	ADDOBJECT(swordKriby);
	
}

void CNomalKirby::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Wall)
	{
		m_groundCounter++;
		m_groundchecker = true;
	}
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Monster && !eat || pOtherCollider->GetOwner()->GetLayer() == Layer::MWeapon)
	{
		if (GAME->HpNotDown == true)
		{
			playerHp -= 0;
		}
		else
		{
			playerHp -= 1;
		}
		GAME->PlayerHit = true;
	}
	if (pOtherCollider->GetObjName() == L"얼음몬스터" && eat)
	{
			ice = true;
	}
	if (pOtherCollider->GetObjName() == L"칼몬스터" && eat)
	{
			sword = true;
	}

	if (pOtherCollider->GetObjName() == L"얼음아이템")
	{
		ice = true;
		Effect(m_vecPos.x);
		effect->kirbyChangeEffect();
		IceKirbyChange();
		m_state = State::Disappear;
	}

	if (pOtherCollider->GetObjName() == L"검아이템")
	{
		sword = true;
		Effect(m_vecPos.x);
		effect->kirbyChangeEffect();
		SwordirbyChange();
		m_state = State::Disappear;
		
	}
}


