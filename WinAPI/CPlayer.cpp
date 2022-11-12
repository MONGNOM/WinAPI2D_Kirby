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
	m_strName = L"�÷��̾�";

	m_Eat = true;
	m_pIdleImageR = nullptr;
	m_pIdleImageD = nullptr;
	m_pIdleImageU = nullptr;
	m_pIdleImageL = nullptr;
	m_pMoveImage = nullptr;
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
	m_pIdleImageR = RESOURCE->LoadImg(L"PlayerIdleR", L"Image\\ICERA.png");
	m_pIdleImageD = RESOURCE->LoadImg(L"PlayerIdleD", L"Image\\ICE1.png");
	m_pIdleImageU = RESOURCE->LoadImg(L"PlayerIdleU", L"Image\\ICE1.png");
	m_pIdleImageL = RESOURCE->LoadImg(L"PlayerIdleL", L"Image\\iceLS.png");
	m_pMoveImage  =	RESOURCE->LoadImg(L"PlayerMove", L"Image\\ICERA.png");
	m_pAttackImage = RESOURCE->LoadImg(L"PlayerAttack", L"Image\\ICERA.png");
	


	m_pAnimator = new CAnimator;
		m_pAnimator->CreateAnimation(L"IdleUp", m_pIdleImageR, Vector(0.f, 0.f), Vector(33.f, 33.f), Vector(29.5f, 0.f), 0.08f, 8);
		m_pAnimator->CreateAnimation(L"IdleRight", m_pIdleImageR, Vector(0.f, 0.f), Vector(33.f, 33.f), Vector(29.5f, 0.f), 0.08f, 8);
		m_pAnimator->CreateAnimation(L"IdleDown", m_pIdleImageR, Vector(0.f, 0.f), Vector(33.f, 33.f), Vector(29.5f, 0.f), 0.08f, 8);
		m_pAnimator->CreateAnimation(L"IdleLeft", m_pIdleImageL, Vector(0.f, 0.f), Vector(25.f, 29.f), Vector(28.f, 0.f), 1.f, 2);

		m_pAnimator->CreateAnimation(L"MoveUp", m_pMoveImage, Vector(0.f, 0.f), Vector(33.f, 33.f), Vector(29.5f, 0.f), 0.08f, 8);
		m_pAnimator->CreateAnimation(L"MoveRight", m_pMoveImage, Vector(0.f, 0.f), Vector(33.f, 33.f), Vector(29.5f, 0.f), 0.08f, 8);
		m_pAnimator->CreateAnimation(L"MoveDown", m_pMoveImage, Vector(0.f, 0.f), Vector(33.f, 33.f), Vector(29.5f, 0.f), 0.08f, 8);
		m_pAnimator->CreateAnimation(L"MoveLeft", m_pMoveImage, Vector(0.f, 0.f), Vector(33.f, 33.f), Vector(29.5f, 0.f), 0.08f, 8);

		m_pAnimator->CreateAnimation(L"IdleRightAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(30.f, 43.f), Vector(30.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"IdleLeftAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(30.f, 43.f), Vector(30.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"IdleDownAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(30.f, 43.f), Vector(30.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"IdleUpAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(30.f, 43.f), Vector(30.f, 0.f), 0.05f, 10);

		m_pAnimator->CreateAnimation(L"MoveRightAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(30.f, 43.f), Vector(30.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveLeftAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(30.f, 43.f), Vector(30.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveUpAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(30.f, 43.f), Vector(30.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveDownAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(30.f, 43.f), Vector(30.f, 0.f), 0.05f, 10);

		m_pAnimator->CreateAnimation(L"IdleUpChange", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);
		m_pAnimator->CreateAnimation(L"IdleRightChange", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);
		m_pAnimator->CreateAnimation(L"IdleDownChange", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);
		m_pAnimator->CreateAnimation(L"IdleLeftChange", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);


		m_pAnimator->CreateAnimation(L"MoveUpChange", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);
		m_pAnimator->CreateAnimation(L"MoveRightChange", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);
		m_pAnimator->CreateAnimation(L"MoveDownChange", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);
		m_pAnimator->CreateAnimation(L"MoveLeftChange", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);


	m_pAnimator->Play(L"IdleUp", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(50, 55), Vector(0, 20));
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
	
	// 3. ���� �� Ÿ�� ���� == ��, �� ���ʿ��� �浹�� è�Ǿ� ��ġ x+ �Ǵ°� �ذ� �ٶ�
	//======================
	
	//========[���� �߿��� ����]����===========
	// �� ���� �ý����� ���� �� �� [�Ϲ� �÷��̾� �۵� �ҷ� �� ����] ==> ���� Ǯ���� ���� �÷��̾� ����
	// �� �������� 1���� �Ϲ��÷��̾�[�Ϲ�Ŀ��]�� ���� �� �� �ٸ� Ŭ������ �÷��̾ �߰�[��Ŀ��]
	// �� 
	// 	// 1. Ư�� ���͸� �Դ´�. == �Դ´�.
	// 2. ���͸� ����Ѵ�.	== �԰� ����Ѵ�.
	// 3. Ư�� ���Ϳ� �´� ������ �Ѵ�. == �԰� ����ϴµ� ���͸� Ư�� ��������Ѵ�.
	// �� ������ ������� �Լ��� ����� ���ǿ� �� Ư�� ���͸� �Ծ����� �̰ɷ� �����Ѵ�.
	// �� �����ϸ� �̹����� �ٲ��� �Ѵ�.
	//=======================
	
	//======�ؾ� �� ���=======
	// 5. �⺻ ==> ���� �̹��� �ٲܼ� �ְ� ������ϴµ� ==> �𸣰ڵ�
	// 6. ���� �����
	// 6.5 �� ������ ���ϰ� �� ��ġ ���Ĵ� ī�޶� Ÿ���� ������ �� ���� ������ ���� �ٽ� è�Ǿ� ����
	// 7. ��ȣ�ۿ�[������] 
	// 7.5. ���� 
	// 8. Ŀ�� ���ҽ� ũ�� ���� == ���ĺ��� ���� �� ũ�� �� �̹��� ������ ũ�� : x: 96�ȼ� y: 64�ȼ�
	//=========================
	
	//=======������========
	// 3. Ư�� ���� ���� [��] == ������ �����߰�����
	// 4. ���� ��� == ���� �̶� �� �ð��Ǹ� �� �ϰ� ����ũ
	// 5. ���� ���� ������Ʈ ����� �ٽ� ������ �ٽ� ���� ��
	//=====================


	//======�ϼ� ���=======
	// 1. �� ��� , �� Ÿ�� ������ �°� ���� ��� ���̸� �ɵ� ���ݸ� 32�����
	// 2. �Ϲ� ���� ����
	// 3. Ư������ ���� 
	// 4. ��� ��� �ϼ�
	// 5. ���� ��� �ϼ�
	// 6. ���� ���� ��� �ϼ�
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
		Logger::Debug(L"Ŀ�� ��ȭ���״�");
		m_Eat = true;

		if (m_LightChange == true)
		{
			Logger::Debug(L"Ŀ�� ������ �����ߴ�");
			DeleteObject(this);
			m_Basic = false;
			LightChange();
		}
	}

	if (BUTTONDOWN('D'))
	{
		if (m_LightChange == true)
		{
			Logger::Debug(L"Ư���ɷ��� �����");
			m_Basic = true;
			m_LightChange = false;
			m_Eat = true;
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

		if (m_LightChange == true)
		{
			DeleteObject(this);
			LightChange();
		
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

void CPlayer::LightChange()
{
	// �� ���� �����ϸ� �ൿ �׸��� �⺻�ൿ�� ���Ƚ�Ű�� ���⿡ ������ �ൿ�� ��Ų��. 
	// ����Ʈ ���� Ŭ���� ���� ������Ʈ �ϳ� �� ������
	// ������ ��������

	ADDOBJECT(LightKirby);

}

void CPlayer::Gravity()
{
	if (m_Gravity == true)
	{
		m_vecPos.y += m_fSpeed * DT * 2;
	}
	else;
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


	if (BUTTONDOWN('S')) str += L"Attack";

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

void CPlayer::Eat()
{
	Logger::Debug(L"���ݿ�����Ʈ ����");

	KirbyEat* m_KE = new KirbyEat;
	if (m_vecLookDir.x > 0)
		m_KE->SetPos(m_vecPos.x + 30, GetPos().y);
	else if (m_vecLookDir.x < 0)
		m_KE->SetPos(m_vecPos.x - 30, GetPos().y);

	m_KE->SetDir(Vector(m_vecPos.x, m_vecMoveDir.y));
	ADDOBJECT(m_KE);
	// �ٸ� Ŭ������ ���ݸ����ͽ��� �����ü��ֳ�
}



void CPlayer::OnCollisionEnter(CCollider* pOtherCollider)
{
	
	if (pOtherCollider->GetObjName() == L"����")
	{
		Logger::Debug(L"���Ϳ� �ε��� �������� �Խ��ϴ�.");
		m_LightChange = false;
		m_Eat = false;
	}

	if (pOtherCollider->GetObjName() == L"������")
	{
		Logger::Debug(L"���Ϳ� �ε��� �������� �Խ��ϴ�.");
		m_LightChange = true;
		m_Eat = false;

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



