#include "framework.h"
#include "CLightMonster.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CPlayer.h"

CLightMonster::CLightMonster()
{
	m_strName = L"빛몬스터";
	m_vecScale = Vector(100, 100);
	m_layer = Layer::SpecialMonster;
	m_vecDir = Vector(0, 0);
	m_fVelocity = 300;
	m_mMoveImage = nullptr;
	m_mDieImage = nullptr;
	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_bIsMove = false;
	m_mHp = 1;
	DieTime = 0;
	Iscrash = false;
	m_mAttackImage = nullptr;
}

CLightMonster::~CLightMonster()
{
}

void CLightMonster::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();

}

void CLightMonster::SetVelocity(float velocity)
{
	m_fVelocity = velocity;

}

void CLightMonster::Init()
{

	m_mMoveImage = RESOURCE->LoadImg(L"BeamMonsterMove", L"Image\\Monster\\BeamMonster\\BeamMonster.png");
	m_mAttackImage = RESOURCE->LoadImg(L"BeamMonsterMoveAttack", L"Image\\Monster\\BeamMonster\\BeamMonsterAttack.png");
	m_mDieImage = RESOURCE->LoadImg(L"BeamMonsterDie", L"Image\\Monster\\BeamMonster\\BeamMonsterDie.png");


	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IdleLeft", m_mMoveImage, Vector(0.f, 100.f), Vector(50.f, 58.f), Vector(70.f, 0.f), 0.15f, 5);
	m_pAnimator->CreateAnimation(L"IdleRight", m_mMoveImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.15f, 5);
	m_pAnimator->CreateAnimation(L"MoveRight", m_mMoveImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.15f, 6);
	m_pAnimator->CreateAnimation(L"MoveLeft", m_mMoveImage, Vector(0.f, 100.f), Vector(50.f, 58.f), Vector(70.f, 0.f), 0.15f, 6);

	m_pAnimator->CreateAnimation(L"IdleLeftDie", m_mDieImage, Vector(0.f, 100.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 1.f, 2);
	m_pAnimator->CreateAnimation(L"IdleRightDie", m_mDieImage, Vector(0.f, 0.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 1.f, 2);
	m_pAnimator->CreateAnimation(L"MoveRightDie", m_mDieImage, Vector(0.f, 0.f), Vector(60.f, 60.f), Vector(60.f, 0.f),	1.f, 2);
	m_pAnimator->CreateAnimation(L"MoveLeftDie", m_mDieImage, Vector(0.f, 100.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 1.f, 2);


	m_pAnimator->Play(L"IdleLeft", false);
	AddComponent(m_pAnimator);


	AddCollider(ColliderType::Rect, Vector(45, 45), Vector(0, 10));

}

void CLightMonster::Update()
{

	Gravity();

	m_vecPos += m_vecDir * m_fVelocity * DT;

	if (Iscrash == true)
	{
		
		DieTime += DT;
		if (DieTime >= 1)
		{

			DELETEOBJECT(this);
			DieTime = 0;
		}
	}

}

void CLightMonster::Render()
{

}

void CLightMonster::Release()
{
}

void CLightMonster::Gravity()
{
	if (m_Gravity == true)
	{
		m_vecPos.y += m_fSpeed * DT * 2;
	}
}

void CLightMonster::AnimatorUpdate()
{

	if (m_vecMoveDir.Length() > 0)
		m_vecLookDir = m_vecMoveDir;

	wstring str = L"";

	if (m_bIsMove)	str += L"Move";
	else			str += L"Idle";

	if (m_vecLookDir.x > 0) str += L"Right";
	else if (m_vecLookDir.x < 0) str += L"Left";

	if (m_mHp == 0) str += L"Die";

	m_pAnimator->Play(str, false);
}

void CLightMonster::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		Logger::Debug(L"몬스터가 플레이어와 부딪혀 데미지를 입습니다.");
		CGameObject* pl = pOtherCollider->GetOwner();
		if (pl->GetPos().x <= m_vecPos.x)
			m_vecPos.x += 100;
		else if (pl->GetPos().x >= m_vecPos.x)
			m_vecPos.x -= 100;
		m_mHp -= 1;
		Iscrash = true;
	}

	if (pOtherCollider->GetObjName() == L"빛 공격")
	{

		Logger::Debug(L"몬스터가 빛공격을 맞았습니다.");
		CGameObject* pl = pOtherCollider->GetOwner();
		if (pl->GetPos().x <= m_vecPos.x)
			m_vecPos.x += 100;
		else if (pl->GetPos().x >= m_vecPos.x)
			m_vecPos.x -= 100;
		Iscrash = true;

	}

	if (pOtherCollider->GetObjName() == L"먹기")
	{
		Logger::Debug(L"몬스터가 빨려가기 시작합니다.");
		CGameObject* pl = pOtherCollider->GetOwner();
		if (pl->GetPos().x <= m_vecPos.x)
			SetDir(Vector(-1, 0));
		else if (pl->GetPos().x >= m_vecPos.x)
			SetDir(Vector(1, 0));

	}

	if (pOtherCollider->GetObjName() == L"Shot")
	{
		Logger::Debug(L"몬스터가 미사일에 맞았습니다");
		DELETEOBJECT(this);
	}
	if (pOtherCollider->GetObjName() == L"땅")
	{

		m_Gravity = false;
	}
}

void CLightMonster::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"먹기")
	{
		Logger::Debug(L"몬스터가 빨려들어가고있습니다.");
	}
	if (pOtherCollider->GetObjName() == L"땅")
	{

		m_Gravity = false;
	}
}

void CLightMonster::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"먹기")
	{
		Logger::Debug(L"몬스터를 먹었습니다.");
		DELETEOBJECT(this);

	}
}
