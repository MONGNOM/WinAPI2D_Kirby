#include "framework.h"
#include "CIceKirby.h"
#include "CIceAttack.h"
#include "CNomalKirby.h"
#include "CGameManager.h"

CIceKirby::CIceKirby()
{
	attackTimer = 0;
	if(GAME->formChange)
	m_state = State::ChangeForm;
	else
	m_state = State::Idle;

	m_pNormalKirby = nullptr;
	m_pAnimator = nullptr;
	m_pIdleImage = nullptr;
	m_pMoveImage = nullptr;
	m_pRunImage = nullptr;
	m_pDownImage = nullptr;
	m_pFlyImage = nullptr;
	m_pJumpImage = nullptr;
	m_pAttackImage = nullptr;
	m_piceAttack = nullptr;
	m_pChangeFormImage = nullptr;
	GAME->sword = false;
	IceSound = RESOURCE->LoadSound(L"IceSound", L"Sound\\IceSkil.wav");
	DropSound = RESOURCE->LoadSound(L"DropSound", L"Sound\\Drop.wav");

}

CIceKirby::~CIceKirby()
{
}


void CIceKirby::Init()
{
	

	GAME->formChange = false;

	CKirby::Init();
	m_pIdleImage	= RESOURCE->LoadImg(L"IceKirbyIdleL",	L"Image\\Kirby\\Ice\\IceKirby.png");
	m_pAttackImage	= RESOURCE->LoadImg(L"IceKirbyAttack",	L"Image\\Kirby\\Ice\\IceKirbyAttackPose.png");
	m_pMoveImage	= RESOURCE->LoadImg(L"IceKirbyW",		L"Image\\Kirby\\Ice\\IceKirbyWalk.png");
	m_pRunImage		= RESOURCE->LoadImg(L"IceKirbyRun",		L"Image\\Kirby\\Ice\\IceKirbyRun.png");
	m_pDownImage	= RESOURCE->LoadImg(L"IceKirbyDown",	L"Image\\Kirby\\Ice\\IceKirbyDown.png");
	m_pFlyImage		= RESOURCE->LoadImg(L"IceKirbyFly",		L"Image\\Kirby\\Ice\\IceKirbyFly.png");
	m_pJumpImage	= RESOURCE->LoadImg(L"IceKirbyJump",	L"Image\\Kirby\\Ice\\IceKirbyJump.png");
	m_pChangeFormImage = RESOURCE->LoadImg(L"IceKirbyChageFormPose",	L"Image\\Kirby\\SwordKirby\\sword kirby change.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IdleR", m_pIdleImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"IdleL", m_pIdleImage, Vector(70.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"RW", m_pMoveImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"LW", m_pMoveImage, Vector(630.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"RRun", m_pRunImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"LRun", m_pRunImage, Vector(490.f, 104.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"RDown", m_pDownImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"LDown", m_pDownImage, Vector(70.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"RAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.04f, 8, false);
	m_pAnimator->CreateAnimation(L"LAttack", m_pAttackImage, Vector(490.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.04f, 6, false);
	m_pAnimator->CreateAnimation(L"RFly", m_pFlyImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 5);
	m_pAnimator->CreateAnimation(L"LFly", m_pFlyImage, Vector(620.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.08f, 5);
	m_pAnimator->CreateAnimation(L"RFlying", m_pFlyImage, Vector(340.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 5);
	m_pAnimator->CreateAnimation(L"LFlying", m_pFlyImage, Vector(270.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.08f, 4);
	m_pAnimator->CreateAnimation(L"RJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.08f, 9,false);
	m_pAnimator->CreateAnimation(L"LJump", m_pJumpImage, Vector(630.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.08f, 9,false);
	m_pAnimator->CreateAnimation(L"RJumping", m_pJumpImage, Vector(480.f, 0.f), Vector(65.f, 50.f), Vector(70.f, 0.f), 0.08f, 2);
	m_pAnimator->CreateAnimation(L"LJumping", m_pJumpImage, Vector(130.f, 100.f), Vector(65.f, 50.f), Vector(-70.f, 0.f), 0.08f, 2);
	m_pAnimator->CreateAnimation(L"RAttacking", m_pAttackImage, Vector(420.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.06f, 2);
	m_pAnimator->CreateAnimation(L"LAttacking", m_pAttackImage, Vector(210.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.06f, 2);
	m_pAnimator->CreateAnimation(L"ChangeFormPose", m_pChangeFormImage, Vector(0.f, 0.f), Vector(45.f, 90.f), Vector(0.f, 0.f), 0.06f, 1);
	m_pAnimator->Play(L"IdleR", false);
	AddComponent(m_pAnimator);
	
	AddCollider(ColliderType::Rect, Vector(40, 40), Vector(0, 0));
}

void CIceKirby::Update()
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
	case State::Attacking:
		AttackingState();
		break;
	case State::Takeoff:
		TakeOffState();
		break;
	case State::ChangeForm:
		ChangeFormState();
		break;
	default:
		break;
	}
	AnimatorUpdate();
}

void CIceKirby::Render()
{
}

void CIceKirby::Release()
{
}

void CIceKirby::AnimatorUpdate()
{
	m_pAnimator->Play(icekirbystate, false);
}

#pragma region 상태패턴 함수

void CIceKirby::Jump()
{
	m_jumpSpeed = 300;
	fallTimer = 0;
	SelectSound(JumpSound, 0.1f, false);

}

void CIceKirby::IdleState()
{
	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * DT;
	}
	if (m_vecLookDir.x == -1)
	{
		icekirbystate = L"IdleL";
	}
	else if (m_vecLookDir.x == 1)
	{
		icekirbystate = L"IdleR";
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
		{
			m_state = State::Walk;
		}
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
		{
			m_state = State::Walk;
		}
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
	if (BUTTONDOWN('D'))
	{
		SOUND->Play(DropSound, 0.5f, false);
		m_state = State::Takeoff;
	}
}

void CIceKirby::WalkState()
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
		icekirbystate = L"LW";
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		m_vecMoveDir.x = 1;
		m_vecPos.x += m_fSpeed * DT;
		icekirbystate = L"RW";

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
	if (BUTTONDOWN('D'))
	{
		SOUND->Play(DropSound, 0.5f, false);
		m_state = State::Takeoff;
	}
}

void CIceKirby::RunState()
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
		icekirbystate = L"LRun";
		m_vecPos.x -= m_fSpeed * DT;
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		effect->SetPos(m_vecPos.x - 35, m_vecPos.y + 5);
		m_vecMoveDir.x = 1;
		icekirbystate = L"RRun";
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
	if (BUTTONDOWN('D'))
	{
		DELETEOBJECT(effect);
		SOUND->Play(DropSound, 0.5f, false);
		m_state = State::Takeoff;
	}
}

void CIceKirby::JumpState()
{
	m_vecPos.y -= m_jumpSpeed * DT;

	if (m_vecLookDir.x == -1)
	{
		icekirbystate = L"LJump";
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
		icekirbystate = L"RJump";
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

void CIceKirby::SitState()
{
	if (m_vecLookDir.x == 1)
	{
		icekirbystate = L"RDown";
		if (BUTTONSTAY(VK_DOWN) && BUTTONSTAY(VK_LEFT))
		{
			m_vecLookDir.x = -1;
			icekirbystate = L"LDown";
		}
	}
	else if (m_vecLookDir.x == -1)
	{
		icekirbystate = L"LDown";
		if (BUTTONSTAY(VK_DOWN) && BUTTONDOWN(VK_LEFT))
		{
			m_vecLookDir.x = 1;
			icekirbystate = L"RDown";
		}
	}
	if (!BUTTONSTAY(VK_DOWN))
		m_state = State::Idle;
}

void CIceKirby::FlyState()
{
	flyTimer += DT;
	//땅에있고  && 0.5초동안 플라이
	m_fSpeed = 100;
	if (m_vecLookDir.x == 1)
	{
		icekirbystate = L"RFly";
		if (flyTimer > 0.4f)
		{
			SelectSound(FlySound, 0.5f, true);
			flyTimer = 0;
			m_state = State::Flying;
		}
	}
	else if (m_vecLookDir.x == -1)
	{
		icekirbystate = L"LFly";
		if (flyTimer > 0.4f)
		{
			SelectSound(FlySound, 0.5f, true);
			flyTimer = 0;
			m_state = State::Flying;

		}
	}
	else if (BUTTONUP(VK_UP))
	{
		m_jumpSpeed = 0;
		m_state = State::JumpingDown;
	}
}


void CIceKirby::AttackState()
{
	if (m_piceAttack == nullptr)
	{
		CreatAttackArea();
	}
	
	attackTimer += DT;

	if (m_vecLookDir.x == -1)
	{
		icekirbystate = L"LAttack";
		if (attackTimer > 0.4f)
		{
			DeleteAttackArea();
			attackTimer = 0;
			m_state = State::Attacking;
		}
	}
	if (m_vecLookDir.x == 1)
	{
		icekirbystate = L"RAttack";
		if (attackTimer > 0.4f)
		{
			DeleteAttackArea();
			attackTimer = 0;
			m_state = State::Attacking;
		}
	}
	if (BUTTONUP('S'))
	{
		DeleteAttackArea();
		m_state = State::Idle;
	}
}

void CIceKirby::AttackingState()
{
	if (m_piceAttack == nullptr)
	{
		CreatAttackArea();
	}
	if (m_vecLookDir.x == -1)
	{
		icekirbystate = L"LAttacking";
	}
	if (m_vecLookDir.x == 1)
	{
		icekirbystate = L"RAttacking";
	}
	if (BUTTONUP('S'))
	{
		DeleteAttackArea();
		m_state = State::Idle;
	}
}


void CIceKirby::JumpingDownState()
{
	m_vecPos.y -= m_jumpSpeed * DT;
	if (m_vecLookDir.x == -1)
	{
		icekirbystate = L"LJumping";
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
		icekirbystate = L"RJumping";
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

void CIceKirby::FlyingState()
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
		icekirbystate = L"RFlying";
	}
	else if (m_vecLookDir.x == -1)
	{
		icekirbystate = L"LFlying";
	}

	if (BUTTONDOWN('S'))
	{
		SOUND->Pause(FlySound);
		m_jumpSpeed = 0;
		m_state = State::JumpingDown;
	}

	m_groundchecker = false;

}

#pragma endregion

void CIceKirby::CreatAttackArea()
{
	SOUND->Play(IceSound, 0.5f, true);
	m_piceAttack = new CIceAttack();
	m_piceAttack->Attack();
	if (m_vecLookDir.x == -1)
	{
		m_piceAttack->SetPos(m_vecPos.x - 50 ,m_vecPos.y);
	}
	if (m_vecLookDir.x == 1)
	{
		m_piceAttack->SetPos(m_vecPos.x + 50, m_vecPos.y); 
	}
	ADDOBJECT(m_piceAttack);
}

void CIceKirby::DeleteAttackArea()
{
	SOUND->Pause(IceSound);
	if (m_piceAttack != nullptr)
	{
		DELETEOBJECT(m_piceAttack);
		m_piceAttack = nullptr;
	}
}

void CIceKirby::TakeOffState()
{
	if (effect != nullptr)
		DELETEOBJECT(effect);
	Effect(m_vecPos.x);
	effect->DropStarEffect();
	effect->effectDestory = true;
	changestar = new CChangeFormStar();
	changestar->SetPos(m_vecPos);
	ADDOBJECT(changestar);
	changestar->ChangeStarName(L"얼음별");
	m_pNormalKirby = new CNomalKirby();
	m_pNormalKirby->SetPos(m_vecPos);
	ADDOBJECT(m_pNormalKirby);
	DELETEOBJECT(this);
	m_pNormalKirby->ice = false;
	
}

void CIceKirby::ChangeFormState()
{
	if (m_groundchecker == false)
	{
		m_vecPos.y += m_gravity * DT;
	}
	
	m_formChangeTimer += DT;
	icekirbystate = L"ChangeFormPose";

	if (m_formChangeTimer > 1.0f)
	{
		CAMERA->FadeIn(0.0001f);
		m_state = State::Idle;
		if (GAME->icePanel)
		{
			panel = new CTransFormPanel();
			panel->GetPos();
			ADDOBJECT(panel);
			GAME->icePanel = false;
			
		}
	}

}

void CIceKirby::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Wall)
	{
		m_groundCounter++;
		m_groundchecker = true;
	}
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Monster)
	{
		if (GAME->HpNotDown == true)
		{
			playerHp -= 0;
		}
		else
		{
			m_state = State::Takeoff;
			SOUND->Play(DamageSound, 0.1f, false);
			playerHp -= 1;
			
		}
		GAME->PlayerHit = true;
	}
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::MWeapon)
	{
		if (GAME->HpNotDown == true)
		{
			playerHp -= 0;
		}
		else
		{
			m_state = State::Takeoff;
			SOUND->Play(DamageSound, 0.1f, false);
			playerHp -= 1;
		}
		GAME->PlayerHit = true;
	}
}

