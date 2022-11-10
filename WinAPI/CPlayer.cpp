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
	ontile = 0;
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Player;
	m_strName = L"�÷��̾�";

	m_Eat = true;
	m_pIdleImage = nullptr;
	m_pMoveImage = nullptr;

	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_bIsMove = false;
	Jumpgo = false;
	JumpTime = 0.f;

	LastJumpTime = 0.f;
	LastRunTime;
	m_Gravity = true;

	
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
	m_pAnimator->Play(L"IdleDown", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(20, 20), Vector(0, 0));
}

void CPlayer::Update()
{
	Gravity();

	m_bIsMove = false;

	//======���� ���=======
	// 1. �޸��� ����
	// �� ����	 [-> + ->]
	// �� ������  [<- + <-]

	// 2. �Ա� ���� 
	// �� �÷��̾ ��� ������ ��ɷ� �ٲ����
	
	// 3. ���� �� Ÿ�� ����  == ���ϼ�
	// 
	//======================
	
	// 1. �� ��� �ֱ� ����
	// 2. �Ϲ� ���� ����
	// 3. Ư�� ���� ���� 
	// 4. ��� ��� ==> �Ա� �� (VK_DOWN) �Ϲ� == ����  Ư�� == ����
	// 5. ���� ���� = �� ���� ����ũ �ҵ� �ϳ��� �Լ� ���� ����
	// 6. ����
	// 7. �̹��� ������


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

	

	if (BUTTONDOWN('S'))
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

	if (BUTTONDOWN('A'))
	{
		Jumpgo = true;
		
	}


	if (Jumpgo == true)
	{
		
		JumpTime += DT;

		 if (JumpTime <= 0.3f)
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
	{
		m_vecPos.y += m_fSpeed * DT * 2;
	}
	else;

}

void CPlayer::Eat()
{
	Logger::Debug(L"���ݿ�����Ʈ ����");

	KirbyEat* m_KE = new KirbyEat;
	if (m_vecLookDir.x > 0)
		m_KE->SetPos(m_vecPos.x + 100, m_vecPos.y);
	else if (m_vecLookDir.x < 0)
	m_KE->SetPos(m_vecPos.x - 100, m_vecPos.y);

	m_KE->SetDir(Vector(m_vecPos.x, m_vecMoveDir.y));
	ADDOBJECT(m_KE);

	// �ٸ� Ŭ������ ���ݸ����ͽ��� �����ü��ֳ�
}


	// ���� �Ҵ� ������ �ϸ� �ȴ���  ���ߴ�
	// delete m_KE;


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
	m_Eat = true;

}

void CPlayer::OnCollisionEnter(CCollider* pOtherCollider)
{
	
	if (pOtherCollider->GetObjName() == L"����")
	{
		Logger::Debug(L"���Ϳ� �ε��� �������� �Խ��ϴ�.");
		m_Eat = false;
		
		 
	}
	
	if (pOtherCollider->GetObjName() == L"��")
	{
		if(ontile >= 1)
		m_Gravity = false;
		++ontile;
	}
	if (pOtherCollider->GetObjName() == L"��")
	{
		CGameObject* B = pOtherCollider->GetOwner();
		
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

	if (pOtherCollider->GetObjName() == L"����")
	{
		Logger::Debug(L"���͸� ���״�?");
		m_Eat = false;
	}
}