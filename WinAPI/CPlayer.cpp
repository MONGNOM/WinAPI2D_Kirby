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
#include "Cassert"
#include "KirbyShot.h"





CPlayer::CPlayer()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Player;
	m_strName = L"플레이어";

	m_pIdleImage = nullptr;
	m_pMoveImage = nullptr;

	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_bIsMove = false;

}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	m_pIdleImage = RESOURCE->LoadImg(L"PlayerIdle", L"Image\\PlayerIdle.png");
	m_pMoveImage = RESOURCE->LoadImg(L"PlayerMove", L"Image\\PlayerMove.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IdleUp", m_pIdleImage, Vector(8.f, 0.f), Vector(80.f, 70.f), Vector(80.f, 0.f), 0.1f, 7);
	m_pAnimator->CreateAnimation(L"IdleRightUp", m_pIdleImage, Vector(8.f, 70.f), Vector(80.f, 70.f), Vector(80.f, 0.f), 0.1f, 7);
	m_pAnimator->CreateAnimation(L"IdleRight", m_pIdleImage, Vector(8.f, 140.f), Vector(80.f, 70.f), Vector(80.f, 0.f), 0.1f, 7);
	m_pAnimator->CreateAnimation(L"IdleRightDown", m_pIdleImage, Vector(8.f, 210.f), Vector(80.f, 70.f), Vector(80.f, 0.f), 0.1f, 7);
	m_pAnimator->CreateAnimation(L"IdleDown", m_pIdleImage, Vector(8.f, 280.f), Vector(80.f, 70.f), Vector(80.f, 0.f), 0.1f, 7);
	m_pAnimator->CreateAnimation(L"IdleLeftDown", m_pIdleImage, Vector(8.f, 350.f), Vector(80.f, 70.f), Vector(80.f, 0.f), 0.1f, 7);
	m_pAnimator->CreateAnimation(L"IdleLeft", m_pIdleImage, Vector(8.f, 420.f), Vector(80.f, 70.f), Vector(80.f, 0.f), 0.1f, 7);
	m_pAnimator->CreateAnimation(L"IdleLeftUp", m_pIdleImage, Vector(8.f, 490.f), Vector(80.f, 70.f), Vector(80.f, 0.f), 0.1f, 7);

	m_pAnimator->CreateAnimation(L"MoveUp", m_pMoveImage, Vector(0.f, 0.f), Vector(80.f, 75.f), Vector(84.f, 0.f), 0.05f, 16);
	m_pAnimator->CreateAnimation(L"MoveRightUp", m_pMoveImage, Vector(0.f, 79.f), Vector(80.f, 75.f), Vector(84.f, 0.f), 0.05f, 16);
	m_pAnimator->CreateAnimation(L"MoveRight", m_pMoveImage, Vector(0.f, 158.f), Vector(80.f, 75.f), Vector(84.f, 0.f), 0.05f, 16);
	m_pAnimator->CreateAnimation(L"MoveRightDown", m_pMoveImage, Vector(0.f, 237.f), Vector(80.f, 75.f), Vector(84.f, 0.f), 0.05f, 16);
	m_pAnimator->CreateAnimation(L"MoveDown", m_pMoveImage, Vector(0.f, 316.f), Vector(80.f, 75.f), Vector(84.f, 0.f), 0.05f, 16);
	m_pAnimator->CreateAnimation(L"MoveLeftDown", m_pMoveImage, Vector(0.f, 395.f), Vector(80.f, 75.f), Vector(84.f, 0.f), 0.05f, 16);
	m_pAnimator->CreateAnimation(L"MoveLeft", m_pMoveImage, Vector(0.f, 474.f), Vector(80.f, 75.f), Vector(84.f, 0.f), 0.05f, 16);
	m_pAnimator->CreateAnimation(L"MoveLeftUp", m_pMoveImage, Vector(0.f, 553.f), Vector(80.f, 75.f), Vector(84.f, 0.f), 0.05f, 16);
	m_pAnimator->Play(L"IdleRight", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(40, 50), Vector(0, 0));
}

void CPlayer::Update()
{
	m_bIsMove = false;
	//=============
	// 달리기 구현
	// ㄴ 왼쪽	 [-> + ->]
	// ㄴ 오른쪽  [<- + <-]
	//=============

	if (BUTTONSTAY(VK_LEFT))
	{	
		m_vecPos.x -= m_fSpeed * DT;
		m_bIsMove = true;
		m_vecMoveDir.x = -1;
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		m_vecPos.x += m_fSpeed * DT;
		m_bIsMove = true;
		m_vecMoveDir.x = +1;
	}
	else
	{
		m_vecMoveDir.x = 0;
	}

	if (BUTTONSTAY('S'))
	{
		//=============
		// 평범한상태 bool 변수를 통해서 이동키를 false로 만들어서 작동못하게 막는다 
		Eat(); 
		m_bIsMove = true;
		
		
		if(1)	// 먹었을때 구현 ==> Eat()에서 몬스터와 접촉하고 몬스터를 먹었다출력이 나오면 구현 
		Shot();
		//=============

	}

	if (BUTTONDOWN('A'))
	{
		//=============
		// 점프구현
		// 1. 중력구현 
		// 2. 땅타일과 마찰 구현 
		// 3. 땅타일과 떨어졌을때 점프 구현 
		// 4. 땅과 접촉해있을때 땅 밑으로 떨어지지 않도록 구현
		// 5. 2단점프 구현[공중부양] ==> [VK_UP] && [A+A]
		// 6. 2단점프 + 공격 [A+A+S] && [VK_UP] 
		//=============
	}



	AnimatorUpdate();
}

void CPlayer::Eat()
{
	Logger::Debug(L"공격오브젝트 생성");

	KirbyEat* m_KE = new KirbyEat;
	if (m_vecLookDir.x > 0) 
	m_KE->SetPos(m_vecPos.x +100, m_vecPos.y);
	else if (m_vecLookDir.x < 0)
	m_KE->SetPos(m_vecPos.x - 100, m_vecPos.y);
	
	m_KE->SetDir(Vector(m_vecPos.x, m_vecMoveDir.y));
	ADDOBJECT(m_KE);

	// 동적 할당 삭제만 하면 된다잉  잘했다
	// delete m_KE;
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

	m_pAnimator->Play(str, false);
}

void CPlayer::Shot()
{
	Logger::Debug(L"Shot");
	KirbyShot* Shot = new KirbyShot;
	Shot->SetPos(m_vecPos);
	Shot->SetDir(Vector(m_vecLookDir.x, m_vecMoveDir.y));
	ADDOBJECT(Shot);

}

void CPlayer::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"몬스터")
	{
		Logger::Debug(L"몬스터와 부딪혀 데미지를 입습니다.");
	}

}

void CPlayer::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CPlayer::OnCollisionExit(CCollider* pOtherCollider)
{
}
