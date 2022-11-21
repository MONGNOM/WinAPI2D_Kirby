#include "framework.h"
#include "CKIngMonster.h"

#include "CCollider.h"
#include "CPlayer.h"

CKIngMonster::CKIngMonster()
{

	m_strName = L"보스 몬스터";
	m_layer = Layer::Monster;
	m_vecScale = Vector(100, 100);
	m_layer = Layer::SpecialMonster;
	m_vecDir = Vector(0, 0);
	m_fVelocity = 300;
	m_mMoveImage = nullptr;
	m_mMoveImageR = nullptr;
	m_mDieImage = nullptr;
	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_bIsMove = false;
	m_mHp = GAME->BossHp;
	DieTime = 0;
	Iscrash = false;
	m_mAttackImage = nullptr;
	m_mJumpImage = nullptr;
	Moveing = true;
	MoveTime = 0;
	Jump2 = false;
	ontile = 0;
}

CKIngMonster::~CKIngMonster()
{

}

void CKIngMonster::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();

}

void CKIngMonster::SetVelocity(float velocity)
{
	m_fVelocity = velocity;

}

void CKIngMonster::Init()
{

	m_mMoveImage = RESOURCE->LoadImg(L"KingMonsterMove", L"Image\\Monster\\King\\KingisBack.png");
	m_mMoveImageR = RESOURCE->LoadImg(L"KingMonsterMoveR", L"Image\\Monster\\King\\KingR.png");
	m_mAttackImage = RESOURCE->LoadImg(L"KingMonsterAttack", L"Image\\Monster\\King\\KingJump.png");
	m_mDieImage = RESOURCE->LoadImg(L"KingMonsterDie", L"Image\\Monster\\King\\KingDie.png");
	m_mJumpImage = RESOURCE->LoadImg(L"KingMonsterJump", L"Image\\Monster\\King\\KingJump.png");


	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IdleLeft", m_mMoveImage, Vector(1358.f, 425.f), Vector(162.f, 200.f), Vector(-194.f, 0.f), 0.15f, 8);
	m_pAnimator->CreateAnimation(L"Idle", m_mMoveImage, Vector(1358.f, 425.f), Vector(162.f, 200.f), Vector(-194.f, 0.f), 0.15f, 8);
	m_pAnimator->CreateAnimation(L"IdleRight", m_mMoveImageR, Vector(0.f, 0.f), Vector(157.f, 177.f), Vector(192.f, 0.f), 0.15f, 8);
	m_pAnimator->CreateAnimation(L"MoveRight", m_mMoveImageR, Vector(0.f, 0.f), Vector(157.f, 177.f), Vector(192.f, 0.f), 0.15f, 8);
	m_pAnimator->CreateAnimation(L"MoveLeft", m_mMoveImage, Vector(1358.f, 425.f), Vector(162.f, 200.f), Vector(-194.f, 0.f), 0.15f, 8);

	m_pAnimator->CreateAnimation(L"IdleLeftDie", m_mDieImage, Vector(680.f, 310.f), Vector(200.f, 200.f), Vector(-240.f, 0.f), 0.5f, 4);
	m_pAnimator->CreateAnimation(L"IdleRightDie", m_mDieImage, Vector(0.f, 0.f), Vector(200.f, 200.f), Vector(240.f, 0.f), 0.5f, 4);
	m_pAnimator->CreateAnimation(L"MoveRightDie", m_mDieImage, Vector(0.f, 0.f), Vector(200.f, 200.f), Vector(240.f, 0.f), 0.5f, 4);
	m_pAnimator->CreateAnimation(L"MoveLeftDie", m_mDieImage, Vector(680.f, 310.f), Vector(200.f, 200.f), Vector(-240.f, 0.f), 0.5f, 4);


	m_pAnimator->CreateAnimation(L"IdleLeftJump", m_mJumpImage, Vector(1260.f, 280.f), Vector(180.f, 210.f), Vector(-215.f, 0.f), 0.1f, 7);
	m_pAnimator->CreateAnimation(L"IdleRightJump", m_mJumpImage, Vector(0.f, 0.f), Vector(180.f, 210.f), Vector(210.f, 0.f), 0.1f, 7);
	m_pAnimator->CreateAnimation(L"MoveRightJump", m_mJumpImage, Vector(0.f, 0.f), Vector(180.f, 210.f), Vector(210.f, 0.f), 0.1f, 7);
	m_pAnimator->CreateAnimation(L"MoveLeftJump", m_mJumpImage, Vector(1260.f, 280.f), Vector(180.f, 210.f), Vector(-215.f, 0.f), 0.1f, 7);


	m_pAnimator->Play(L"Idle", false);
	AddComponent(m_pAnimator);


	AddCollider(ColliderType::Rect, Vector(150, 150), Vector(0, 12));
}

void CKIngMonster::Update()
{
	Move();

	GAME->BossHp = m_mHp;

	if (m_mHp <= 0)
	{
		Iscrash = true;
		Jump2 = false;
		Moveing = false;
	}
	Gravity();

	m_vecPos += m_vecDir * m_fVelocity * DT;

	if (Iscrash == true)
	{
		DieTime += DT;
		if (DieTime >= 2)
		{
			DELETEOBJECT(this);
			DieTime = 0;
		}
	}



	if (Jump2 == true)
	{
		JumpTime += DT;
		if (JumpTime <= 0.3f)
		{
			Logger::Debug(L"왼쪽 점프");
			m_vecPos.y -= m_fSpeed * DT * 5;
			m_vecPos.x -= 7;
			str = L"IdleLeft";

		}
		else if (JumpTime >= 0.3f && JumpTime <= 2.3f)
		{
			Logger::Debug(L"왼쪽 Look");
			m_vecLookDir = Vector(-1, 0);
			str = L"IdleLeft";
		}
		else if (JumpTime >= 2.3f && JumpTime <= 2.6f)
		{
			Logger::Debug(L"오른쪽 점프");
			m_vecPos.y -= m_fSpeed * DT * 5;
			m_vecPos.x += 7;
			str = L"IdleRight";

	
		}
		else if (JumpTime >= 2.6f && JumpTime <= 4.6f)
		{
			Logger::Debug(L"오른쪽 Look");
			m_vecLookDir = Vector(1, 0);
			str = L"IdleRight";
		}
		else if (JumpTime >= 4.6f)
		{
			
			JumpTime = 0;
			Jump2 = false;
		}
	}

	AnimatorUpdate();
}

void CKIngMonster::Render()
{
}

void CKIngMonster::Release()
{
}

void CKIngMonster::Gravity()
{
	if (m_Gravity == true)
	{
		m_vecPos.y += m_fSpeed * DT * 2;
	}
}


void CKIngMonster::Move()
{
	if (Moveing == true)
	{
		MoveTime += DT;
		if (MoveTime <= 3)
		{
			m_vecLookDir = Vector(-1, 0);
		}
		else if (MoveTime >= 3 && MoveTime <= 14.5)
		{
			m_vecPos.x -= 50 * DT;
			m_vecLookDir = Vector(-1, 0);
		}
		else if (MoveTime >= 14.5 && MoveTime <= 17.5)
		{
			m_vecLookDir = Vector(1, 0);
		}
		else if (MoveTime >= 17.5 && MoveTime <= 29)
		{
			m_vecPos.x += 50 * DT;
			m_vecLookDir = Vector(1, 0);
		}
		else if (MoveTime >= 29 && MoveTime <= 32)
		{
			m_vecLookDir = Vector(-1, 0);
		}
		else
		{
			Jump2 = true;
			MoveTime = 0;
		}
	}
}

void CKIngMonster::AnimatorUpdate()
{
	if (m_vecMoveDir.Length() > 0)
		m_vecLookDir = m_vecMoveDir;

	wstring str = L"";

	if (m_bIsMove)	str += L"Move";
	else			str += L"Idle";

	if (m_vecLookDir.x > 0) str += L"Right";
	else if (m_vecLookDir.x < 0) str += L"Left";

	if (m_mHp <= 0) str += L"Die";
	
	if (Jump2 == true) str += L"Jump";

	m_pAnimator->Play(str, false);
}

void CKIngMonster::OnCollisionEnter(CCollider* pOtherCollider)
{


	if (pOtherCollider->GetObjName() == L"빛 공격")
	{
		Logger::Debug(L"몬스터가 빛공격을 맞았습니다.");
		CGameObject* pl = pOtherCollider->GetOwner();
		if (pl->GetPos().x <= m_vecPos.x)
			m_vecPos.x += 0;
		else if (pl->GetPos().x >= m_vecPos.x)
			m_vecPos.x -= 0;
		
		m_mHp -= 1;

	}




	if (pOtherCollider->GetObjName() == L"Shot")
	{
		Logger::Debug(L"몬스터가 미사일에 맞았습니다");
		m_mHp -= 1;
	}

	if (pOtherCollider->GetObjName() == L"땅")
	{
		if (ontile >= 1)
			m_Gravity = false;
		++ontile;
	}
}

void CKIngMonster::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"먹기")
	{
		Logger::Debug(L"몬스터가 빨려들어가고있습니다.");
	}
	if (pOtherCollider->GetObjName() == L"땅")
	{
		if (ontile >= 1)
			m_Gravity = false;
	}
}

void CKIngMonster::OnCollisionExit(CCollider* pOtherCollider)
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
