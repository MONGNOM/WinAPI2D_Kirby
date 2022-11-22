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
	ontile = 0;
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Player;
	m_strName = L"�÷��̾�";

	m_Hp = false;
	m_Eat = true;
	m_pIdleImageR = nullptr;
	m_pIdleImageU = nullptr;
	m_pIdleImageL = nullptr;
	m_pMoveImageR = nullptr;
	m_pMoveImageL = nullptr;
	m_pAttackImage = nullptr;

	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
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
	m_pRunImageR = nullptr;
	m_pRunImageL = nullptr;
	m_pIdleImageRD = nullptr;
	m_pIdleImageLD = nullptr;
	m_pAttackImageRD = nullptr;
	m_pAttackImageLD = nullptr;
	m_pJumpImage = nullptr;
	m_KirbyEatImage = nullptr;
	flySound = false;

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

	m_pRunImageR  = RESOURCE->LoadImg(L"PlayerRunR", L"Image\\Kirby\\Basic\\KirbyRun.png");
	m_pRunImageL  = RESOURCE->LoadImg(L"PlayerRunL", L"Image\\Kirby\\Basic\\KirbyRun.png");

	m_KirbyEatImage = RESOURCE->LoadImg(L"PlayerEat", L"Image\\Kirby\\Basic\\KirbyEatRun.png");
	m_KirbyEatDownImage = RESOURCE->LoadImg(L"PlayerEatDown", L"Image\\Kirby\\Basic\\KirbyDiner.png");



	// ĳ���� 45x43�ȼ�
	
	m_pAnimator = new CAnimator;
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
		m_pAnimator->CreateAnimation(L"IdleRightUpJumpEat", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleRightJumpEat", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleLeftUpJumpEat", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleLeftJumpEat", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);

		m_pAnimator->CreateAnimation(L"MoveRightUpJumpEat", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"MoveRightJumpEat", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"MoveLeftUpJumpEat", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"MoveLeftJumpEat", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"MoveRightRunJumpEat", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"MoveLeftRunJumpEat", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);

		m_pAnimator->CreateAnimation(L"IdleRunJumpEat", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleRightRunJumpEat", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);
		m_pAnimator->CreateAnimation(L"IdleLeftRunJumpEat", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9, false);

		//		������ ���� �ٿ��� ��� �̹���==========

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

		
		m_pAnimator->CreateAnimation(L"IdleRun", m_pRunImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
		m_pAnimator->CreateAnimation(L"IdleRightRun", m_pRunImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
		m_pAnimator->CreateAnimation(L"IdleLeftRun", m_pRunImageR, Vector(490.f, 104.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 8);

		m_pAnimator->CreateAnimation(L"IdleRightUpRun", m_pRunImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
		m_pAnimator->CreateAnimation(L"IdleLeftUpRun", m_pRunImageR, Vector(490.f, 104.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 8);


		m_pAnimator->CreateAnimation(L"MoveUpRun", m_pRunImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
		m_pAnimator->CreateAnimation(L"MoveRightRun", m_pRunImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
		m_pAnimator->CreateAnimation(L"MoveLeftRun", m_pRunImageR, Vector(490.f, 104.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 8);

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
	======���ҽ� ���=====
	1. �Ϲ� Ŀ��	== [�Ϸ�] ==> ���ҽ� �ൿ���Ǹ� �ɸ� �� �Ա� ��� ��� �����ϸ� ��
	3. ����	[�Ϲ�] == [�Ϸ�] 
	4. Ư�� ���� [��, ����] == [�Ϸ�]
	5. ����   ==[�ε�] [�ϼ�]
	5.5 �� Ŀ�� & ����Ŀ�� [�ϼ�] 
	=====���� �ڵ� �߰� �ʿ�=====
	===�÷��̾� �ڵ� �߰� �ʿ�======
	6. �� ���� & ������ ����� 
	7. ��ȣ�ۿ� [��] == ������Ʈ ����
	8. UI [ü�¹� ���Ż���]  == ü�¹ٰ� ���µ� �ǹ���
	=====================
	


	======���� ���=======
	 1. �޸��� ����
	 �� ����	 [-> + ->]
	 �� ������  [<- + <-]

	===�÷��̾� �ڵ� �߰� �ʿ�====== > Ư���ൿ�ÿ� ���ϰԲ�?
 	======================
	

	=======�߿�============
	 2. �̹����ذ��ؾ��� ==> Ư���ൿ�ϸ� Ư�� ���۸������Բ� ������ ��������
	 3. �÷��̾� ���� ������Ʈ�� ������ ����
	=================


	=======������==========

	 4. ���� = �������ݻ��� �� ���ݻ���  ���� �������� 
	=====================



	======�ϼ� ���=======
	 1. �� ��� , �� Ÿ�� ������ �°� ���� ��� ���̸� �ɵ� ���ݸ� 32�����
	 2. �Ϲ� ���� ����
	 3. Ư������ ���� 
	 4. ��� ��� �ϼ�
	 5. ���� ��� �ϼ�
	 6. ���� ���� ��� �ϼ�
	 7. ���� ���� �ϼ� [���� �Ϲ� Ư��]
	 8. ��ȣ�ۿ�[�� == Ư����ư�� ������]
	 9. ����Ŀ�� �ϼ� 
	 10. ü�¹� ����
	 11. Ÿ��Ʋȭ��
	 12. UI �ϼ�
	 13. Ŀ�� ü��, �ɷ°���
	 14. ���� ü�� ����
	 15. ���ҽ� �ϼ�
	 16. ���� �̵�
	 17. ���� ���� �̹��� ����
	 18. Ŀ�� ����
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

	if (BUTTONSTAY(VK_LEFT))
	{
		LastRunTime += DT;
		if (BUTTONSTAY('R')/*LastRunTime <= 0.15f && BUTTONSTAY(VK_LEFT)*/)
		{
			m_vecPos.x -= m_fSpeed * DT * 2.f;
			m_bIsMove = true;
			m_vecMoveDir.x = -1;
			LastRunTime = 0;

		}
		else if (BUTTONSTAY(VK_DOWN)/*LastRunTime <= 0.15f && BUTTONSTAY(VK_LEFT)*/)
		{
			m_vecMoveDir.x = -1;
			m_bIsMove = false;
		}
		else if (BUTTONSTAY('R') && BUTTONSTAY(VK_DOWN)/*LastRunTime <= 0.15f && BUTTONSTAY(VK_LEFT)*/)
		{
			m_vecMoveDir.x = -1;
			m_bIsMove = false;
		}
		else if (BUTTONSTAY('S'))
		{
			m_vecMoveDir.x = 0;
			m_bIsMove = false;
		}
		else
		{
			m_vecPos.x -= m_fSpeed * DT;
			m_bIsMove = true;
			m_vecMoveDir.x = -1;
		}
	}

	else if (BUTTONSTAY(VK_RIGHT))
	{
		LastRunTime += DT;
		if(BUTTONSTAY('R') /*&& LastRunTime <= 0.15f && BUTTONSTAY(VK_RIGHT)*/)
		{ 
			m_vecPos.x += m_fSpeed * DT *2.f;
			m_bIsMove = true;
			m_vecMoveDir.x = +1;
			LastRunTime = 0;
		}
		else if (BUTTONSTAY('S'))
		{
			m_vecMoveDir.x = 0;
			m_bIsMove = false;
		}

		else if (BUTTONSTAY(VK_DOWN)/*LastRunTime <= 0.15f && BUTTONSTAY(VK_LEFT)*/)
		{
			m_vecMoveDir.x = +1;
			m_bIsMove = false;
		}

		else if (BUTTONSTAY(VK_DOWN) && BUTTONSTAY('R'))/*LastRunTime <= 0.15f && BUTTONSTAY(VK_LEFT)*/
		{
			m_vecMoveDir.x = +1;
			m_bIsMove = false;
		}
		else
		{
			m_vecPos.x += m_fSpeed * DT;
			m_bIsMove = true;
			m_vecMoveDir.x = +1;
		}
	}

	else
	{
		m_vecMoveDir.x = 0;
	}

	if (m_Eat == false && BUTTONDOWN(VK_DOWN))
	{
		CSound* Change = RESOURCE->LoadSound(L"Change", L"Sound\\Change.Wav");

		Logger::Debug(L"Ŀ�� ��ȭ���״�");
		m_Eat = true;

		if (m_LightChange == true)
		{
			SOUND->Play(Change, 0.1f, false);

			Logger::Debug(L"Ŀ�� ������ �����ߴ�");
			m_Basic = false;
			ChangePlayer();
		}
		else if (m_IceChange == true)
		{
			SOUND->Play(Change, 0.1f,false);

			Logger::Debug(L"Ŀ�� �������� �����ߴ�");
			m_Basic = false;
			ChangePlayer();
		}
	}

	if (BUTTONSTAY(VK_DOWN) && BUTTONDOWN('S'))
	{

		m_vecPos.x += m_fSpeed * DT +100; 
		// �ð� �־ �� �ð���ŭ �� �Ÿ��� �̵��ϰ� �� ����
	}

	if (BUTTONDOWN('S'))
	{
		CSound* Eattingsound = RESOURCE->LoadSound(L"Eatting", L"Sound\\Eatting.Wav");
		CSound* Shotsound = RESOURCE->LoadSound(L"Shot", L"Sound\\Shot.Wav");
		if (m_Basic == true)
		{
			if (m_Eat)  //true
			{
				Eat();
				SOUND->Play(Eattingsound, 0.1f,false);
		
			}
			else // false
			{
				Shot();
				SOUND->Play(Shotsound, 0.1f, false);
			
			}
		}
	}
	


	if (BUTTONDOWN('A'))
	{
		flyTime += DT;
		Jumpgo = true;
		CSound* Jumpsound = RESOURCE->LoadSound(L"Jump", L"Sound\\Jump.Wav");
		SOUND->Play(Jumpsound, 0.1f,false);

		/*if (flyTime <= 0.15f)
		{
			Logger::Debug(L"����");
			m_vecPos.y -= m_fSpeed * DT * 4;
			flyTime = 0;

		}*/
	}


	if (BUTTONSTAY(VK_UP))
	{
			
		JumpTime += DT; 
			
			
			if (JumpTime <= 0.4f)
			{
				Logger::Debug(L"����");
				m_vecPos.y -= m_fSpeed * DT * 3;
			}
			else
			{
				JumpTime = 0;
				Jumpgo = false;
			}
	}
	if (BUTTONDOWN(VK_UP))
	{
		SOUND->Play(flysound, 0.1f, true);
	}
	if (BUTTONUP(VK_UP))
	{
		SOUND->Pause(flysound);
	}

	if (Jumpgo == true)
	{
		JumpTime += DT;

		if (JumpTime <= 0.4f)
		{
			Logger::Debug(L"����");
			m_vecPos.y -= m_fSpeed * DT * 4;
		}
		else
		{
			JumpTime = 0;
			Jumpgo = false;
		}
	}

		AnimatorUpdate();
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


void CPlayer::AnimatorUpdate()
{

	wstring str = L"";

	if (m_vecMoveDir.Length() > 0)
		m_vecLookDir = m_vecMoveDir;

	if (m_bIsMove)	str += L"Move";
	else			str += L"Idle";

	if (m_vecLookDir.x > 0) str += L"Right";
	else if (m_vecLookDir.x < 0) str += L"Left";

	if (BUTTONSTAY(VK_UP)  &&  m_Gravity == true && m_vecPos.y) str += L"Up";

	

	if (BUTTONDOWN('A') && m_vecPos.y >= 300 && m_Gravity == true ) str += L"flyDown";

	if (BUTTONSTAY(VK_DOWN)) str += L"Down";

	if (BUTTONSTAY(VK_DOWN) && m_Eat == false) str += L"ChangeDown";


	if (BUTTONSTAY('S')) str += L"Attack";

	if (BUTTONSTAY('R')) str += L"Run";

	if (BUTTONSTAY('A')|| m_vecPos.y >= 300 && m_Gravity == true) str += L"Jump";

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
	Logger::Debug(L"���ݿ�����Ʈ ����");

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
	// �ٸ� Ŭ������ ���ݸ����ͽ��� �����ü��ֳ�
}



void CPlayer::OnCollisionEnter(CCollider* pOtherCollider)
{
	CSound* Eatsound = RESOURCE->LoadSound(L"Eat", L"Sound\\Eat.Wav");
	
	if (pOtherCollider->GetObjName() == L"����")
	{
		Logger::Debug(L"���Ϳ� �ε��� �������� �Խ��ϴ�.");
	
			m_LightChange = false;
			m_IceChange = false;
			Light = false;
			Ice = false;
			SOUND->Play(Eatsound, 0.1f, false);

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
	if (pOtherCollider->GetObjName() == L"���� ����")
	{
		SOUND->Play(Eatsound, 0.1f, false);

		Logger::Debug(L"���Ϳ� �ε��� �������� �Խ��ϴ�.");
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


	if (pOtherCollider->GetObjName() == L"������")
	{
		Logger::Debug(L"���Ϳ� �ε��� �������� �Խ��ϴ�.");
		Ice = false;
		Light = true;
		SOUND->Play(Eatsound, 0.1f, false);
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
	
	if (pOtherCollider->GetObjName() == L"�Ա�")
	{
		Logger::Debug(L"���͸� ���״�?");
		CGameObject* Eat = pOtherCollider->GetOwner();
		
	}

	if (pOtherCollider->GetObjName() == L"��")
	{
		if(ontile >= 1)
		m_Gravity = false;
		++ontile;
	}

	if (pOtherCollider->GetObjName() == L"���� ����")
	{
		Logger::Debug(L"���Ϳ� �ε��� �������� �Խ��ϴ�.");
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
	if (pOtherCollider->GetObjName() == L"��")
	{	
		if (ontile >= 1)
		m_Gravity = false;
	}
}

void CPlayer::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"��")
	{
		--ontile;
		if (ontile == 0)
		{
			m_Gravity = true;
		}
	}
}



