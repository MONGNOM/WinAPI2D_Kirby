#include "framework.h"
#include "CPlayer.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"
#include "CMonster.h"

#include "CMissile.h"
#include "KirbyEat.h"
#include "KirbyShot.h"
#include "CLightKirby.h"
#include "CIceKirby.h"
#include "CGameManager.h"
#include "CKirbyHp.h"





CPlayer::CPlayer()
{
	state = Playerstate::Idle;

	ontile = 0;
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Player;
	m_strName = L"플레이어";

	m_Hp = false;
	m_Eat = true;
	m_pIdleImageR = nullptr;
	m_pIdleImageU = nullptr;
	m_pIdleImageL = nullptr;
	m_pMoveImageR = nullptr;
	m_pMoveImageL = nullptr;
	m_pAttackImage = nullptr;

	m_vecInputDir = Vector(0, 0);
	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(1, 0);
	m_bIsMove = false;
	Jumpgo = false;
	JumpTime = 0.f;
	m_Basic = true;
	m_KirbyEatDownImage = nullptr;
	m_LightChange = false;
	LastJumpTime = 0.f;
	LastRunTime = 0;
	m_Gravity = true;
	m_pChangeImage = nullptr;
	LightKirby = nullptr;
	m_pRunImage = nullptr;
	m_pRunImageL = nullptr;
	m_pIdleImageRD = nullptr;
	m_pIdleImageLD = nullptr;
	m_pAttackImageRD = nullptr;
	m_pAttackImageLD = nullptr;
	m_pJumpImage = nullptr;
	m_KirbyEatImage = nullptr;

	m_pHp = GAME->PlayerHp;
	Light = false;
	Ice = false;
	m_IceChange = false;
	flyTime = 0;

	KirbyNoHit = false;
	NoHitTime = 0;
}


CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	
	m_pAttackImage = RESOURCE->LoadImg(L"PlayerAttack", L"Image\\Kirby\\Basic\\KirbyEat.png");


	m_pChangeImage = RESOURCE->LoadImg(L"LightPlayerChange", L"Image\\Kirby\\Light\\LightKirbyChange.png");

	m_pAttackImageRD = RESOURCE->LoadImg(L"PlayerDownAttackR", L"Image\\Kirby\\Basic\\KirbyDownAttack.png");
	m_pIdleImageR = RESOURCE->LoadImg(L"PlayerIdleR", L"Image\\Kirby\\Basic\\KirbyIdleR.png");
	m_pIdleImageRD = RESOURCE->LoadImg(L"PlayerIdleRD", L"Image\\Kirby\\Basic\\KirbyDown.png");
	
	m_pIdleImageU = RESOURCE->LoadImg(L"PlayerIdleU", L"Image\\Kirby\\Basic\\KirbyFly.png");
	m_pIdleImageL = RESOURCE->LoadImg(L"PlayerIdleL", L"Image\\Kirby\\Basic\\KirbyIdleL.png");
	
	m_pMoveImageR = RESOURCE->LoadImg(L"PlayerMoveR", L"Image\\Kirby\\Basic\\KirbyRW.png");
	m_pMoveImageL = RESOURCE->LoadImg(L"PlayerMoveL", L"Image\\Kirby\\Basic\\KirbyLW.png");
	
	m_pJumpImage = RESOURCE->LoadImg(L"PlayerJump", L"Image\\Kirby\\Basic\\KirbyJump.png");

	m_pRunImage  = RESOURCE->LoadImg(L"PlayerRunR", L"Image\\Kirby\\Basic\\KirbyRun.png");

	m_KirbyEatImage = RESOURCE->LoadImg(L"PlayerEat", L"Image\\Kirby\\Basic\\KirbyEatRun.png");
	m_KirbyEatDownImage = RESOURCE->LoadImg(L"PlayerEatDown", L"Image\\Kirby\\Basic\\KirbyDiner.png");


	m_pAnimator = new CAnimator;
	// IDLE
	m_pAnimator->CreateAnimation(L"LeftIdle", m_pIdleImageL, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
	m_pAnimator->CreateAnimation(L"RightIdle", m_pIdleImageR, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);

	// WALK
	m_pAnimator->CreateAnimation(L"LeftWalk", m_pMoveImageL, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"RightWalk", m_pMoveImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);

	// RUN
	m_pAnimator->CreateAnimation(L"LeftRun", m_pRunImage, Vector(0.f, 104.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"RightRun", m_pRunImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);

	// 캐릭터 45x43픽셀
	
	m_pAnimator->CreateAnimation(L"IdleUPDown", m_pChangeImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 10.0f, 1);

		m_pAnimator->CreateAnimation(L"IdleDownUP", m_pChangeImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleUp", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20, false);
		m_pAnimator->CreateAnimation(L"IdleRightUp", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20, false);
		m_pAnimator->CreateAnimation(L"IdleRight", m_pIdleImageR, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"Idle", m_pIdleImageR, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleRightDown", m_pIdleImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(43.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleDown", m_pIdleImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(50.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleLeft", m_pIdleImageL, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleLeftDown", m_pIdleImageRD, Vector(0.f, 100.f), Vector(50.f, 50.f), Vector(50.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleLeftUp", m_pIdleImageU, Vector(0.f, 100.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20, false);

		//eat
		m_pAnimator->CreateAnimation(L"IdleUpEat", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20, false);
		m_pAnimator->CreateAnimation(L"IdleRightUpEat", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20, false);
		m_pAnimator->CreateAnimation(L"IdleRightEat", m_KirbyEatImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(0.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleRightRunEat", m_KirbyEatImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(0.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleEat", m_KirbyEatImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(0.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleRightDownEatChangeDown", m_KirbyEatDownImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(43.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleDownEatChangeDown", m_KirbyEatDownImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(50.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleLeftEat", m_KirbyEatImage, Vector(0.f, 100.f), Vector(60.f, 50.f), Vector(0.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleLeftRunEat", m_KirbyEatImage, Vector(0.f, 100.f), Vector(60.f, 50.f), Vector(0.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleLeftDownEatChangeDown", m_KirbyEatDownImage, Vector(0.f, 100.f), Vector(50.f, 50.f), Vector(50.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleLeftUpEat", m_pIdleImageU, Vector(0.f, 100.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20, false);

		m_pAnimator->CreateAnimation(L"MoveUpEat", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20);
		m_pAnimator->CreateAnimation(L"MoveRightEat", m_KirbyEatImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 16);
		m_pAnimator->CreateAnimation(L"MoveRightRunEat", m_KirbyEatImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 16);
		m_pAnimator->CreateAnimation(L"MoveRightUpEat", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20);
		m_pAnimator->CreateAnimation(L"MoveRightUpRunEat", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20);
		m_pAnimator->CreateAnimation(L"MoveRightDownEat", m_KirbyEatDownImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveLeftDownEat", m_KirbyEatDownImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveLeftEat", m_KirbyEatImage, Vector(0.f, 100.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 16);
		m_pAnimator->CreateAnimation(L"MoveLeftRunEat", m_KirbyEatImage, Vector(0.f, 100.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 16);
		m_pAnimator->CreateAnimation(L"MoveLeftUpEat", m_pIdleImageU, Vector(0.f, 100.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20);
		m_pAnimator->CreateAnimation(L"MoveLeftUpRunEat", m_pIdleImageU, Vector(0.f, 100.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20);


		m_pAnimator->CreateAnimation(L"IdleAttackEat", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5, false);
		m_pAnimator->CreateAnimation(L"IdleUpAttackEat", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5, false);
		m_pAnimator->CreateAnimation(L"IdleRightUpAttackEat", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5, false);
		m_pAnimator->CreateAnimation(L"IdleRightAttackEat", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5, false);
		m_pAnimator->CreateAnimation(L"IdleLeftUpAttackEat", m_pAttackImage, Vector(0.f, 100.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5, false);
		m_pAnimator->CreateAnimation(L"IdleLeftAttackEat", m_pAttackImage, Vector(0.f, 100.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5, false);


		m_pAnimator->CreateAnimation(L"MoveRightAttackEat", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5, false);
		m_pAnimator->CreateAnimation(L"MoveLeftAttackEat", m_pAttackImage, Vector(0.f, 100.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5, false);
		m_pAnimator->CreateAnimation(L"MoveUpAttackEat", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5, false);
		m_pAnimator->CreateAnimation(L"MoveAttackEat", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5, false);

		m_pAnimator->CreateAnimation(L"IdleJumpEat", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleRightJumpEat", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleLeftJumpEat", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);

		m_pAnimator->CreateAnimation(L"MoveRightJumpEat", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"MoveLeftJumpEat", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);

		m_pAnimator->CreateAnimation(L"MoveRightRunJumpEat", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"MoveLeftRunJumpEat", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);

		m_pAnimator->CreateAnimation(L"IdleRunJumpEat", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleRightRunJumpEat", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleLeftRunJumpEat", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);

		//		어택은 낫잇 다운은 디너 이미지==========

		m_pAnimator->CreateAnimation(L"IdleRightDownRun", m_pIdleImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(43.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"MoveRightDownRun", m_pIdleImageRD, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveLeftDownRun", m_pIdleImageRD, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"IdleLeftDownRun", m_pIdleImageRD, Vector(0.f, 100.f), Vector(50.f, 50.f), Vector(50.f, 0.f), 10.0f, 1);

		m_pAnimator->CreateAnimation(L"MoveRightUpRun", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20);
		m_pAnimator->CreateAnimation(L"MoveLeftUpRun", m_pIdleImageU, Vector(0.f, 100.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20);


		m_pAnimator->CreateAnimation(L"MoveUp", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20);
		m_pAnimator->CreateAnimation(L"MoveRight", m_pMoveImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveRightUp", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20);
		m_pAnimator->CreateAnimation(L"MoveRightDown", m_pIdleImageRD, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveLeftDown", m_pIdleImageRD, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveLeft", m_pMoveImageL, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveLeftUp", m_pIdleImageU, Vector(0.f, 100.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20);

		m_pAnimator->CreateAnimation(L"IdleAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5,false);
		m_pAnimator->CreateAnimation(L"IdleUpAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5, false);
		m_pAnimator->CreateAnimation(L"IdleRightUpAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5, false);
		m_pAnimator->CreateAnimation(L"IdleRightAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5,false);
		m_pAnimator->CreateAnimation(L"IdleLeftUpAttack", m_pAttackImage, Vector(0.f, 100.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5, false);
		m_pAnimator->CreateAnimation(L"IdleLeftAttack", m_pAttackImage, Vector(0.f, 100.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5, false);
		m_pAnimator->CreateAnimation(L"IdleRightDownAttack", m_pAttackImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.5f, 2);
		m_pAnimator->CreateAnimation(L"IdleDownAttack", m_pAttackImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.5f, 2);
		m_pAnimator->CreateAnimation(L"IdleLeftDownAttack", m_pAttackImageRD, Vector(0.f, 100.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.5f, 2);

		m_pAnimator->CreateAnimation(L"IdleRightAttackRun", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleLeftAttackRun", m_pAttackImage, Vector(0.f, 100.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9, false);

		m_pAnimator->CreateAnimation(L"IdleRightUpAttackRun", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleLeftUpAttackRun", m_pAttackImage, Vector(0.f, 100.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9, false);


		m_pAnimator->CreateAnimation(L"MoveRightAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5,false);
		m_pAnimator->CreateAnimation(L"MoveLeftAttack", m_pAttackImage, Vector(0.f, 100.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5, false);
		m_pAnimator->CreateAnimation(L"MoveUpAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5, false);
		m_pAnimator->CreateAnimation(L"MoveDownRightAttack", m_pAttackImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.5f, 2, false);
		m_pAnimator->CreateAnimation(L"MoveDownLeftAttack", m_pAttackImageRD, Vector(0.f, 100.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.5f, 2, false);
		m_pAnimator->CreateAnimation(L"MoveAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 5, false);

		
		m_pAnimator->CreateAnimation(L"IdleRun", m_pRunImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
		m_pAnimator->CreateAnimation(L"IdleRightRun", m_pRunImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
		m_pAnimator->CreateAnimation(L"IdleLeftRun", m_pRunImage, Vector(490.f, 104.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 8);

		m_pAnimator->CreateAnimation(L"IdleRightUpRun", m_pRunImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
		m_pAnimator->CreateAnimation(L"IdleLeftUpRun", m_pRunImage, Vector(490.f, 104.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 8);


		m_pAnimator->CreateAnimation(L"MoveUpRun", m_pRunImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
		m_pAnimator->CreateAnimation(L"MoveRightRun", m_pRunImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
		m_pAnimator->CreateAnimation(L"MoveLeftRun", m_pRunImage, Vector(490.f, 104.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 8);

		m_pAnimator->CreateAnimation(L"MoveRightUpAttackRun", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"MoveLeftUpAttackRun", m_pAttackImage, Vector(0.f, 100.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"MoveRightAttackRunJump", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"MoveLeftAttackRunJump", m_pAttackImage, Vector(0.f, 100.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);

		m_pAnimator->CreateAnimation(L"MoveRightAttackRun", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"MoveLeftAttackRun", m_pAttackImage, Vector(0.f, 100.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"MoveUpAttackRun", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);


		m_pAnimator->CreateAnimation(L"IdleJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleJumpflyDown", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleUpJump", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20 , false);
		m_pAnimator->CreateAnimation(L"IdleRightUpJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleRightJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleRightflyDownJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9,false);
		m_pAnimator->CreateAnimation(L"IdleLeftUpJump", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleLeftJump", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9,false);

		m_pAnimator->CreateAnimation(L"MoveRightfltDownJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"MoveRightJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"MoveRightflyDownJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"MoveRightUpJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"MoveLeftJump", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"MoveLeftUpJump", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
	
		m_pAnimator->CreateAnimation(L"MoveRightRunJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"MoveRightflyDownRunJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"MoveRightUpRunJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"MoveLeftRunJump", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"MoveLeftflyDownRunJump", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"MoveLeftUpRunJump", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);

		m_pAnimator->CreateAnimation(L"IdleRunJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleRightRunJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleRightUpRunJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleLeftRunJump", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleLeftUpRunJump", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);


		m_pAnimator->CreateAnimation(L"IdleAttackJump", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"IdleRightAttackJump", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"IdleLeftAttackJump", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);

		m_pAnimator->CreateAnimation(L"MoveRightAttackJump", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"MoveLeftAttackJump", m_pAttackImage, Vector(0.f, 100.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"MoveAttackJump", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);

	m_pAnimator->Play(L"IdleUp", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(45, 45), Vector(0, 0));
}

void CPlayer::Update()
{

	Gravity();
	m_bIsMove = false;
	/*
	======리소스 명단=====
	1. 일반 커비	== [완료] ==> 리소스 행동조건만 걸면 됌 먹기 뱉기 흡수 적용하면 됌
	3. 몬스터	[일반] == [완료] 
	4. 특별 몬스터 [빛, 얼음] == [완료]
	5. 보스   ==[두두] [완성]
	5.5 빛 커비 & 얼음커비 [완성] 
	=====몬스터 코드 추가 필요=====
	===플레이어 코드 추가 필요======
	6. 맵 수정 & 보스맵 만들기 
	7. 상호작용 [문] == 오브젝트 생성
	8. UI [체력바 변신상태]  == 체력바가 없는데 실벌탱
	=====================
	


	======보류 명단=======
	 1. 달리기 구현
	 ㄴ 왼쪽	 [-> + ->]
	 ㄴ 오른쪽  [<- + <-]

	===플레이어 코드 추가 필요====== > 특정행동시에 못하게끔?
 	======================
	

	=======중요============
	 2. 이미지해결해야함 ==> 특정행동하면 특정 동작만나오게끔 보스도 마찬가지
	=================


	=======진행중==========
	 3. 플레이어 공격 오브젝트가 도망감 ㅋㅋ

	 4. 사운드
	=====================



	======완성 명단=======
	 1. 뒷 배경 , 맵 타일 사이즈 맞게 수정 요망 줄이면 될듯 조금만 32배수로
	 2. 일반 몬스터 구현
	 3. 특수몬스터 구현 
	 4. 흡수 기능 완성
	 5. 변신 기능 완성
	 6. 변신 벗기 기능 완성
	 7. 몬스터 구현 완성 [보스 일반 특별]
	 8. 상호작용[문 == 특정버튼시 보스방]
	 9. 얼음커비 완성 
	 10. 체력바 구현
	 11. 타이틀화면
	 12. UI 완성
	 13. 커비 체력, 능력공유
	 14. 보스 체력 구현
	 15. 리소스 완성
	 16. 몬스터 이동
	 17. 방향 따라 이미지 변경
	 18. 커비 무적
	=====================
	*/

	GAME->PlayerPos = m_vecPos;
	GAME->PlayerHp = m_pHp;

	if (m_pHp <= 0)
	{
		DELETEOBJECT(this);
	}

	if (GAME->changePlayerIce == true || GAME->changePlayerLight == true)
	{
		ChangePlayer();
		GAME->changePlayerIce = false;
		GAME->changePlayerLight = false;
		GAME->Changeice = false;
		GAME->ChangeLight = false;
	}

	// 입력
	if (BUTTONSTAY(VK_LEFT))
		m_vecInputDir.x = -1;
	else if (BUTTONSTAY(VK_RIGHT))
		m_vecInputDir.x = 1;
	else
		m_vecInputDir.x = 0;

	if (state == Playerstate::Idle)
	{		


		// Handle Animator
		if (m_vecInputDir.Length() > 0)
			m_vecLookDir = m_vecInputDir;
		if (m_vecLookDir.x > 0) m_pAnimator->Play(L"RightIdle");
		else if (m_vecLookDir.x < 0) m_pAnimator->Play(L"LeftIdle");


		// Input Handle
		if (BUTTONDOWN('S') && m_Eat)		state = Playerstate::Eat;
		else if (BUTTONDOWN('S') && !m_Eat) state = Playerstate::Shot;
		else if (BUTTONDOWN(VK_DOWN))		state = Playerstate::Change;
		else if (BUTTONDOWN('A'))			state = Playerstate::Jump;
		else if (BUTTONSTAY(VK_UP))			state = Playerstate::Fly;
		else if (m_vecInputDir.x != 0)
		{
			if (BUTTONSTAY('R'))	state = Playerstate::Run;
			else					state = Playerstate::Walk;
		}
	}
	else if (state == Playerstate::Walk)
	{
		// 움직임
		m_vecPos.x += m_fSpeed * DT * m_vecInputDir.x;

		// Handle Animator
		if (m_vecInputDir.Length() > 0)
			m_vecLookDir = m_vecInputDir;
		if (m_vecLookDir.x > 0) m_pAnimator->Play(L"RightWalk");
		else if (m_vecLookDir.x < 0) m_pAnimator->Play(L"LeftWalk");


		// Input Handle
		if (BUTTONDOWN('S') && m_Eat)		state = Playerstate::Eat;
		else if (BUTTONDOWN('S') && !m_Eat) state = Playerstate::Shot;
		else if (BUTTONDOWN(VK_DOWN))		state = Playerstate::Change;
		else if (BUTTONDOWN('A'))			state = Playerstate::Jump;
		else if (BUTTONSTAY(VK_UP))			state = Playerstate::Fly;
		else if (m_vecInputDir.x == 0)		state = Playerstate::Idle;
		else if (BUTTONSTAY('R'))			state = Playerstate::Run;

	}
	else if (state == Playerstate::Run)
	{
		// 움직임
		m_vecPos.x += m_fSpeed * DT * m_vecInputDir.x * 2;

		// Handle Animator
		if (m_vecInputDir.Length() > 0)
			m_vecLookDir = m_vecInputDir;
		if (m_vecLookDir.x > 0) m_pAnimator->Play(L"RightRun");
		else if (m_vecLookDir.x < 0) m_pAnimator->Play(L"LeftRun");

		// Input Handle
		if (BUTTONDOWN('S') && m_Eat)		state = Playerstate::Eat;
		else if (BUTTONDOWN('S') && !m_Eat) state = Playerstate::Shot;
		else if (BUTTONDOWN(VK_DOWN))		state = Playerstate::Change;
		else if (BUTTONDOWN('A'))			state = Playerstate::Jump;
		else if (BUTTONSTAY(VK_UP))			state = Playerstate::Fly;
		else if (m_vecInputDir.x == 0)		state = Playerstate::Idle;
		else if (!BUTTONSTAY('R'))			state = Playerstate::Walk;
	}
	else if (state == Playerstate::Jump)
	{

	}
	else if (state == Playerstate::Fly)
	{

	}
	else if (state == Playerstate::Shot)
	{

	}
	else if (state == Playerstate::Eat)
	{

	}
	else if (state == Playerstate::Change)
	{

	}

	/*
	if (BUTTONSTAY(VK_DOWN) && BUTTONDOWN('S'))
	{
		Sliding();
	}
	else if (BUTTONSTAY('S'))
	{
		Attack();
	}
	else if (m_Eat == false && BUTTONDOWN(VK_DOWN))
	{
		FormChange();
	}
	else if (BUTTONDOWN('A'))
	{
		Jump();
	}
	else if (BUTTONSTAY(VK_UP))
	{
		Fly();
	}
	else if (BUTTONSTAY(VK_LEFT) || BUTTONSTAY(VK_RIGHT))
	{
		if (BUTTONSTAY('R')) Run();
		else Walk();
	}
	*/

	//	if (BUTTONSTAY('R')/*LastRunTime <= 0.15f && BUTTONSTAY(VK_LEFT)*/)
	//	{
	//		m_vecPos.x -= m_fSpeed * DT * 2.f;
	//		m_bIsMove = true;
	//		m_vecMoveDir.x = -1;
	//		LastRunTime = 0;

	//	}
	//	else if (BUTTONSTAY(VK_DOWN)/*LastRunTime <= 0.15f && BUTTONSTAY(VK_LEFT)*/)
	//	{
	//		m_vecMoveDir.x = -1;
	//		m_bIsMove = false;
	//	}
	//	else if (BUTTONSTAY('R') && BUTTONSTAY(VK_DOWN)/*LastRunTime <= 0.15f && BUTTONSTAY(VK_LEFT)*/)
	//	{
	//		m_vecMoveDir.x = -1;
	//		m_bIsMove = false;
	//	}
	//	else if (BUTTONSTAY('S'))
	//	{
	//		m_vecMoveDir.x = 0;
	//		m_bIsMove = false;
	//	}
	//	else
	//	{
	//		m_vecPos.x -= m_fSpeed * DT;
	//		m_bIsMove = true;
	//		m_vecMoveDir.x = -1;
	//	}
	//}

	//else if (BUTTONSTAY(VK_RIGHT))
	//{
	//	LastRunTime += DT;
	//	if (BUTTONSTAY('R') /*&& LastRunTime <= 0.15f && BUTTONSTAY(VK_RIGHT)*/)
	//	{
	//		m_vecPos.x += m_fSpeed * DT * 2.f;
	//		m_bIsMove = true;
	//		m_vecMoveDir.x = +1;
	//		LastRunTime = 0;
	//	}
	//	else if (BUTTONSTAY('S'))
	//	{
	//		m_vecMoveDir.x = 0;
	//		m_bIsMove = false;
	//	}

	//	else if (BUTTONSTAY(VK_DOWN)/*LastRunTime <= 0.15f && BUTTONSTAY(VK_LEFT)*/)
	//	{
	//		m_vecMoveDir.x = +1;
	//		m_bIsMove = false;
	//	}

	//	else if (BUTTONSTAY(VK_DOWN) && BUTTONSTAY('R'))/*LastRunTime <= 0.15f && BUTTONSTAY(VK_LEFT)*/
	//	{
	//		m_vecMoveDir.x = +1;
	//		m_bIsMove = false;
	//	}
	//	else
	//	{
	//		m_vecPos.x += m_fSpeed * DT;
	//		m_bIsMove = true;
	//		m_vecMoveDir.x = +1;
	//	}
	//}


	if (Jumpgo == true)
	{
		JumpTime += DT;

		if (JumpTime <= 0.4f)
		{
			Logger::Debug(L"점프");
			m_vecPos.y -= m_fSpeed * DT * 4;
		}
		else
		{
			JumpTime = 0;
			Jumpgo = false;
		}
	}
}

void CPlayer::Gravity()
{
	if (m_Gravity == true)
		m_vecPos.y += m_fSpeed * DT * 2;
	

}
	
void CPlayer::Render()
{
}

void CPlayer::Release()
{
	
}

void CPlayer::Walk()
{
	m_vecMoveDir = m_vecInputDir;
	m_vecPos.x -= m_fSpeed * DT * m_vecMoveDir.x;
}

void CPlayer::Run()
{
	m_vecMoveDir = m_vecInputDir * 2.f;
	m_vecPos.x -= m_fSpeed * DT * m_vecMoveDir.x;
}

void CPlayer::Attack()
{
	if (m_Basic == true)
	{
		if (m_Eat)  //true
		{
			Eat();
		}
		else // false
		{
			Shot();
		}
	}
}

void CPlayer::Jump()
{
	flyTime += DT;
	Jumpgo = true;
	CSound* sound = RESOURCE->LoadSound(L"Jump", L"Sound\\Jump.Wav");
	SOUND->Play(sound, 0.1f, false);

	/*if (flyTime <= 0.15f)
	{
		Logger::Debug(L"점프");
		m_vecPos.y -= m_fSpeed * DT * 4;
		flyTime = 0;

	}*/
}

void CPlayer::Fly()
{
	JumpTime += DT;

	if (JumpTime <= 0.4f)
	{
		Logger::Debug(L"점프");
		m_vecPos.y -= m_fSpeed * DT * 3;
	}
	else
	{
		JumpTime = 0;
		Jumpgo = false;
	}
}

void CPlayer::Sliding()
{
}

void CPlayer::FormChange()
{
	Logger::Debug(L"커비가 소화시켰다");
	m_Eat = true;

	if (m_LightChange == true)
	{
		Logger::Debug(L"커비가 빛으로 변신했다");
		m_Basic = false;
		ChangePlayer();
	}
	else if (m_IceChange == true)
	{
		Logger::Debug(L"커비가 얼음으로 변신했다");
		m_Basic = false;
		ChangePlayer();
	}
}


void CPlayer::AnimatorUpdate()
{

	wstring str = L"";

	if (m_vecMoveDir.Length() > 0)
		m_vecLookDir = m_vecMoveDir;

	if (m_vecLookDir.x > 0) str += L"Right";
	else if (m_vecLookDir.x < 0) str += L"Left";

	// IDLE
	if (m_vecMoveDir.Length() <= 0)
	{
		str += L"Idle";
		m_pAnimator->Play(str, false);
		return;
	}


	if (BUTTONSTAY(VK_UP) && m_vecPos.y <= 300 && m_Gravity == true) str += L"Up";

	

	if (BUTTONDOWN('A') && m_vecPos.y >= 300 && m_Gravity == true ) str += L"flyDown";

	if (BUTTONSTAY(VK_DOWN)) str += L"Down";

	if (BUTTONSTAY(VK_DOWN) && m_Eat == false) str += L"ChangeDown";


	if (BUTTONSTAY('S')) str += L"Attack";

	if (BUTTONSTAY('R')) str += L"Run";

	if (BUTTONSTAY('A') || m_Gravity == true) str += L"Jump";

	if (m_Eat == false) str += L"Eat";




	m_pAnimator->Play(str, false);
}

void CPlayer::Shot()
{
	Logger::Debug(L"Shot");
	KirbyShot* Shot = new KirbyShot;
	Shot->SetPos(m_vecPos);
	Shot->SetDir(Vector(m_vecLookDir.x, m_vecMoveDir.y));
	ADDOBJECT(Shot);
	m_Eat = true;
  
}

void CPlayer::ChangePlayer()
{
	if (Light == true)
	{
		GAME->ChangeLight = true;
		CGameObject* lightKirby = new CLightKirby();
		lightKirby->SetPos(m_vecPos);
		ADDOBJECT(lightKirby);
		GAME->changePlayerLight = true;
		DELETEOBJECT(this);
	}
	else if (Ice == true)
	{
		GAME->Changeice = true;
		CGameObject* IceKirby = new CIceKirby();
		IceKirby->SetPos(m_vecPos);
		ADDOBJECT(IceKirby);
		GAME->changePlayerIce = true;

		DELETEOBJECT(this);
	}
}

void CPlayer::Eat()
{
	Logger::Debug(L"공격오브젝트 생성");

	KirbyEat* m_KE = new KirbyEat;
	if (m_vecLookDir.x > 0)
		m_KE->SetPos(m_vecPos.x + 30, GetPos().y);
	else if (m_vecLookDir.x < 0)
		m_KE->SetPos(m_vecPos.x - 30, GetPos().y);

	m_KE->SetDir(Vector(m_vecPos.x, m_vecMoveDir.y));
	if (BUTTONSTAY(VK_DOWN))
		DELETEOBJECT(m_KE);
	else
	ADDOBJECT(m_KE);
	// 다른 클래스의 온콜리전익싯을 가져올수있나
}



void CPlayer::OnCollisionEnter(CCollider* pOtherCollider)
{
	
	if (pOtherCollider->GetObjName() == L"몬스터")
	{
		Logger::Debug(L"몬스터와 부딪혀 데미지를 입습니다.");
	
			m_LightChange = false;
			m_IceChange = false;
			Light = false;
			Ice = false;
	
		if (BUTTONSTAY('S'))
		{
			m_Eat = false;
		}
		if (GAME->HpNotDown == true || BUTTONSTAY('S'))
		{
			m_pHp -= 0;

		}
		else
		{
			m_pHp -= 1;
		}
		GAME->PlayerHit = true;

	}
	if (pOtherCollider->GetObjName() == L"얼음 몬스터")
	{
		Logger::Debug(L"몬스터와 부딪혀 데미지를 입습니다.");
		Light = false;
		m_IceChange = true;
		Ice = true;
		m_LightChange = false;
		if (BUTTONSTAY('S'))
		{
			m_Eat = false;
		}

		if (GAME->HpNotDown == true || BUTTONSTAY('S'))
		{
			m_pHp -= 0;

		}
		else
		{
			m_pHp -= 1;
		}
		GAME->PlayerHit = true;



	}


	if (pOtherCollider->GetObjName() == L"빛몬스터")
	{
		Logger::Debug(L"몬스터와 부딪혀 데미지를 입습니다.");
		Ice = false;
		Light = true;
		m_LightChange = true;
		if (BUTTONSTAY('S'))
		{
			m_Eat = false;
		}
		if (GAME->HpNotDown == true || BUTTONSTAY('S'))
		{
			m_pHp -= 0;

		}
		else
		{
			m_pHp -= 1;
		}
		GAME->PlayerHit = true;
		m_IceChange = false;


	}
	
	if (pOtherCollider->GetObjName() == L"먹기")
	{
		Logger::Debug(L"몬스터를 삼켰다?");
		CGameObject* Eat = pOtherCollider->GetOwner();
		
	}

	if (pOtherCollider->GetObjName() == L"땅")
	{
		if(ontile >= 1)
		m_Gravity = false;
		++ontile;
	}

	if (pOtherCollider->GetObjName() == L"보스 몬스터")
	{
		Logger::Debug(L"몬스터와 부딪혀 데미지를 입습니다.");
		m_LightChange = false;

		if (GAME->HpNotDown == true)
		{
			m_pHp -= 0;

		}
		else
		{
			m_pHp -= 1;
		}
		GAME->PlayerHit = true;




		Light = false;
		m_IceChange = false;
		Ice = false;
		



	}
}




void CPlayer::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"땅")
	{	
		if (ontile >= 1)
		m_Gravity = false;
	}
}

void CPlayer::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"땅")
	{
		--ontile;
		if (ontile == 0)
		{
			m_Gravity = true;
		}
	}
}



