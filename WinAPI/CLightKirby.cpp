#include "framework.h"
#include "CLightKirby.h"

#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"
#include "CMonster.h"

#include "CMissile.h"
#include "KirbyEat.h"
#include "KirbyShot.h"
#include "LightKirbyShot.h"

CLightKirby::CLightKirby()
{
	ontile = 0;
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Player;
	m_strName = L"플레이어";

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
	LastJumpTime = 0.f;
	LastRunTime;
	m_Gravity = true;
	m_pChangeImage = nullptr;
}

CLightKirby::~CLightKirby()
{
}

void CLightKirby::Init()
{

	m_pChangeImage = RESOURCE->LoadImg(L"PlayerChange", L"Image\\SparkKirby2.png");
	m_pAttackImage = RESOURCE->LoadImg(L"PlayerAttack", L"Image\\SparkKirby2.png");




	m_pAnimator = new CAnimator;

	m_pAnimator->CreateAnimation(L"IdleUp", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);
	m_pAnimator->CreateAnimation(L"IdleRight", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);
	m_pAnimator->CreateAnimation(L"IdleDown", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);
	m_pAnimator->CreateAnimation(L"IdleLeft", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);


	m_pAnimator->CreateAnimation(L"MoveUp", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);
	m_pAnimator->CreateAnimation(L"MoveRight", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);
	m_pAnimator->CreateAnimation(L"MoveDown", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);
	m_pAnimator->CreateAnimation(L"MoveLeft", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);

	m_pAnimator->CreateAnimation(L"IdleRightAttack", m_pChangeImage, Vector(0.f, 0.f), Vector(30.f, 43.f), Vector(30.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"IdleLeftAttack", m_pChangeImage, Vector(0.f, 0.f), Vector(30.f, 43.f), Vector(30.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"IdleDownAttack", m_pChangeImage, Vector(0.f, 0.f), Vector(30.f, 43.f), Vector(30.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"IdleUpAttack", m_pChangeImage, Vector(0.f, 0.f), Vector(30.f, 43.f), Vector(30.f, 0.f), 0.05f, 10);

	m_pAnimator->CreateAnimation(L"MoveRightAttack", m_pChangeImage, Vector(0.f, 0.f), Vector(30.f, 43.f), Vector(30.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"MoveLeftAttack", m_pChangeImage, Vector(0.f, 0.f), Vector(30.f, 43.f), Vector(30.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"MoveUpAttack", m_pChangeImage, Vector(0.f, 0.f), Vector(30.f, 43.f), Vector(30.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"MoveDownAttack", m_pChangeImage, Vector(0.f, 0.f), Vector(30.f, 43.f), Vector(30.f, 0.f), 0.05f, 10);



	m_pAnimator->Play(L"IdleRight", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(50, 55), Vector(0, 20));



}

void CLightKirby::Update()
{
	Gravity();
	m_bIsMove = false;


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

		if (BUTTONSTAY('R')/*LastRunTime <= 0.15f && BUTTONSTAY(VK_RIGHT)*/)
		{
			m_vecPos.x += m_fSpeed * DT * 2.f;
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


	if (BUTTONDOWN('D'))
	{
		Logger::Debug(L"특수능력을 뱉었다");
		BasicKirby();
	}

	if (BUTTONDOWN('S'))
	{
		Logger::Debug(L"빛 공격이다");
		LigthAttack();
		
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

void CLightKirby::Render()
{
}

void CLightKirby::Release()
{
}




void CLightKirby::Gravity()
{
	if (m_Gravity == true)
		m_vecPos.y += m_fSpeed * DT * 2;
}



void CLightKirby::AnimatorUpdate()
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


void CLightKirby::LigthAttack()
{

	LightKirbyShot* LightAttack = new LightKirbyShot;
	if (m_vecLookDir.x > 0)
		LightAttack->SetPos(m_vecPos.x + 30, GetPos().y);
	else if (m_vecLookDir.x < 0)
		LightAttack->SetPos(m_vecPos.x - 30, GetPos().y);

	LightAttack->SetDir(Vector(m_vecPos.x, m_vecMoveDir.y));
	ADDOBJECT(LightAttack);

}

void CLightKirby::BasicKirby()
{

	Logger::Debug(L"커비가 능력을 뱉었다.");

	CGameObject* BasicKirby = new CPlayer;
	BasicKirby->SetPos(m_vecPos);
	ADDOBJECT(BasicKirby);

	CAMERA->SetTargetObj(BasicKirby);

	DELETEOBJECT(this);

}

void CLightKirby::OnCollisionEnter(CCollider* pOtherCollider)
{

	if (pOtherCollider->GetObjName() == L"몬스터")
	{
		Logger::Debug(L"몬스터와 부딪혀 데미지를 입습니다.");
		CGameObject* Mob = pOtherCollider->GetOwner();
		DeleteObject(this);
	}

	if (pOtherCollider->GetObjName() == L"빛몬스터")
	{
		Logger::Debug(L"몬스터와 부딪혀 데미지를 입습니다.");
		CGameObject* Mob2 = pOtherCollider->GetOwner();
		DeleteObject(this);

	}

	if (pOtherCollider->GetObjName() == L"땅")
	{
		if (ontile >= 1)
			m_Gravity = false;
		++ontile;
	}
}

void CLightKirby::OnCollisionStay(CCollider* pOtherCollider)
{

	if (pOtherCollider->GetObjName() == L"땅")
	{
		if (ontile >= 1)
			m_Gravity = false;
	}
}

void CLightKirby::OnCollisionExit(CCollider* pOtherCollider)
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
