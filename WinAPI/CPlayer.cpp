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






CPlayer::CPlayer()
{
	ontile = 0;
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Player;
	m_strName = L"플레이어";

	m_Eat = true;
	m_pIdleImageR = nullptr;
	m_pIdleImageD = nullptr;
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

	m_LightChange = false;
	LastJumpTime = 0.f;
	LastRunTime;
	m_Gravity = true;
	m_pChangeImage = nullptr;
	LightKirby = nullptr;
	
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	m_pIdleImageR = RESOURCE->LoadImg(L"PlayerIdleR", L"Image\\KirbyIdleR.png");
	m_pIdleImageD = RESOURCE->LoadImg(L"PlayerIdleD", L"Image\\KirbyIdleR.png");
	m_pIdleImageU = RESOURCE->LoadImg(L"PlayerIdleU", L"Image\\KirbyIdleR.png");
	m_pIdleImageL = RESOURCE->LoadImg(L"PlayerIdleL", L"Image\\KirbyIdleL.png");
	m_pMoveImageR = RESOURCE->LoadImg(L"PlayerMoveR", L"Image\\KirbyRW.png");
	m_pMoveImageL = RESOURCE->LoadImg(L"PlayerMoveL", L"Image\\KirbyLW.png");
	m_pAttackImage = RESOURCE->LoadImg(L"PlayerAttack", L"Image\\iceRA.png");
	
	// 캐릭터 45x43픽셀
	
	m_pAnimator = new CAnimator;
		m_pAnimator->CreateAnimation(L"IdleUp", m_pIdleImageD, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleRight", m_pIdleImageD, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleDown", m_pIdleImageD, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleLeft", m_pIdleImageL, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);

		m_pAnimator->CreateAnimation(L"MoveUp", m_pMoveImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveRight", m_pMoveImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveDown", m_pMoveImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveLeft", m_pMoveImageL, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);

		m_pAnimator->CreateAnimation(L"IdleRightAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 0.03f, 1);
		m_pAnimator->CreateAnimation(L"IdleLeftAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleDownAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleUpAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);

		m_pAnimator->CreateAnimation(L"MoveRightAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(10.f, 10.f), Vector(45.f, 0.f), 10.0f, 3);
		m_pAnimator->CreateAnimation(L"MoveLeftAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"MoveUpAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"MoveDownAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);


	m_pAnimator->Play(L"IdleUp", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(45, 45), Vector(0, 0));
}

void CPlayer::Update()
{
	Gravity();
	m_bIsMove = false;

	//======보류 명단=======
	// 1. 달리기 구현
	// ㄴ 왼쪽	 [-> + ->]
	// ㄴ 오른쪽  [<- + <-]

	// 2. 먹기 오류 
	// ㄴ 플레이어가 닿는 판정을 어떤걸로 바꿔야함
	
	// 3. 벽과 땅 타일 구분 == 밑, 위 왼쪽에서 충돌시 챔피언 위치 x+ 되는거 해결 바람
	//======================
	
	//========[제일 중요한 구현]변신===========
	// ㄴ 변신 시스템을 변신 할 때 [일반 플레이어 작동 불로 다 멈춤] ==> 변신 풀리면 변신 플레이어 멈춤
	// ㄴ 스테이지 1에서 일반플레이어[일반커비]를 삭제 할 때 다른 클래스의 플레이어를 추가[빛커비]
	// 빛으로 변신했을때 공격을 안한다. ???
	
	//========================================
	
	//======해야 할 명단=======
	// 5. 기본 ==> 변신 이미지 바꿀수 있게 해줘야하는데 ==> 모르겠따
	// 6. 보스 만들기
	// 6.5 맵 사이즈 정하고 그 위치 이후는 카메라 타켓팅 날리고 그 범위 안으로 오면 다시 챔피언 고정
	// 7. 상호작용[아이템] 
	// 7.5. 보류 
	// 8. 커비 리소스 크기 수정 == 쿠파보다 조금 더 크게 ㄱ 이미지 입히기 크기 : x: 96픽셀 y: 64픽셀
	//=========================
	
	//=======진행중========
	// 3. 특수 몬스터 구현 [완] == 빛만완 얼음추가예정
	// 4. 변신 기능 == 얼음 이랑 빛 시간되면 불 하고 스파크
	// 5. 변신 벗기 오브젝트 만들고 다시 먹으면 다시 변신 ㄱ
	//=====================


	//======완성 명단=======
	// 1. 뒷 배경 , 맵 타일 사이즈 맞게 수정 요망 줄이면 될듯 조금만 32배수로
	// 2. 일반 몬스터 구현
	// 3. 특수몬스터 구현 
	// 4. 흡수 기능 완성
	// 5. 변신 기능 완성
	// 6. 변신 벗기 기능 완성
	//=====================



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
		
		if(BUTTONSTAY('R')/*LastRunTime <= 0.15f && BUTTONSTAY(VK_RIGHT)*/)
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
		Logger::Debug(L"커비가 소화시켰다");
		m_Eat = true;

		if (m_LightChange == true)
		{
			Logger::Debug(L"커비가 빛으로 변신했다");
			DeleteObject(this);
			m_Basic = false;
			ChangePlayer();
		}
		
	}


	if (BUTTONDOWN('S'))
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

	if (BUTTONDOWN('A'))
	{
		Jumpgo = true;
	}


	if (Jumpgo == true)
	{
		JumpTime += DT;

		if (JumpTime <= 0.3f)
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
	if (m_vecMoveDir.Length() > 0)
		m_vecLookDir = m_vecMoveDir;

	wstring str = L"";
	
	if (m_bIsMove)	str += L"Move";
	else			str += L"Idle";

	if (m_vecLookDir.x > 0) str += L"Right";
	else if (m_vecLookDir.x < 0) str += L"Left";

	if (m_vecLookDir.y > 0) str += L"Up";
	else if (m_vecLookDir.y < 0) str += L"Down";


	if (BUTTONSTAY('S')) str += L"Attack";

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
	CGameObject* lightKirby = new CLightKirby();
	lightKirby->SetPos(m_vecPos);
	ADDOBJECT(lightKirby);

	CAMERA->SetTargetObj(lightKirby);

	DELETEOBJECT(this);
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
	ADDOBJECT(m_KE);
	// 다른 클래스의 온콜리전익싯을 가져올수있나
}



void CPlayer::OnCollisionEnter(CCollider* pOtherCollider)
{
	
	if (pOtherCollider->GetObjName() == L"몬스터")
	{
		Logger::Debug(L"몬스터와 부딪혀 데미지를 입습니다.");
		m_LightChange = false;
		m_Eat = false;
	}

	if (pOtherCollider->GetObjName() == L"빛몬스터")
	{
		Logger::Debug(L"몬스터와 부딪혀 데미지를 입습니다.");
		m_LightChange = true;
		m_Eat = false;

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



