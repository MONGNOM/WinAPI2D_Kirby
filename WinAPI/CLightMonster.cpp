#include "framework.h"
#include "CLightMonster.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CPlayer.h"

CLightMonster::CLightMonster()
{
	m_strName = L"������";
	m_vecScale = Vector(100, 100);
	m_layer = Layer::SpecialMonster;
	m_vecDir = Vector(0, 0);
	m_fVelocity = 300;
<<<<<<< HEAD
	m_mMoveImage = nullptr;
	m_mDieImage = nullptr;
	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_bIsMove = false;
	m_mHp = 1;
	DieTime = 0;
	Iscrash = false;
	m_mAttackImage = nullptr;
	 slide = false;
	 slideTime = 0;
=======
>>>>>>> parent of 812e713 (feat : 보스 몬스터 및 플레이어 변신 및 상호작용 문 구현)
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
	AddCollider(ColliderType::Rect, Vector(90, 90), Vector(0, 0));

}

void CLightMonster::Update()
{

	if (slide == true)
	{
		slideTime += DT;
		if (slideTime <= 0.1f)
		{
			if (GAME->PlayerPos.x <= m_vecPos.x)
				m_vecPos.x += m_fSpeed * DT * 3;

			else if (GAME->PlayerPos.x >= m_vecPos.x)
				m_vecPos.x -= m_fSpeed * DT * 3;

			slideTime = 0;
		}
	}
	Gravity();

	m_vecPos += m_vecDir * m_fVelocity * DT;


}

void CLightMonster::Render()
{
	RENDER->FrameRect(
		m_vecPos.x - m_vecScale.x * 0.5f,
		m_vecPos.y - m_vecScale.y * 0.5f,
		m_vecPos.x + m_vecScale.x * 0.5f,
		m_vecPos.y + m_vecScale.y * 0.5f);
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

void CLightMonster::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
	{
		Logger::Debug(L"���Ͱ� �÷��̾�� �ε��� �������� �Խ��ϴ�.");
<<<<<<< HEAD
		
		m_mHp -= 1;
		Iscrash = true;
		slide = true;
	}

	if (pOtherCollider->GetObjName() == L"�� ����")
	{

		Logger::Debug(L"���Ͱ� �������� �¾ҽ��ϴ�.");
		CGameObject* pl = pOtherCollider->GetOwner();
		slide = true;
		Iscrash = true;

=======
		DELETEOBJECT(this);
>>>>>>> parent of 812e713 (feat : 보스 몬스터 및 플레이어 변신 및 상호작용 문 구현)
	}

	if (pOtherCollider->GetObjName() == L"�Ա�")
	{
		Logger::Debug(L"���Ͱ� �������� �����մϴ�.");
		CGameObject* pl = pOtherCollider->GetOwner();
		if (pl->GetPos().x <= m_vecPos.x)
			SetDir(Vector(-1, 0));
		else if (pl->GetPos().x >= m_vecPos.x)
			SetDir(Vector(1, 0));

	}

	if (pOtherCollider->GetObjName() == L"Shot")
	{
		Logger::Debug(L"���Ͱ� �̻��Ͽ� �¾ҽ��ϴ�");
		DELETEOBJECT(this);
	}
	if (pOtherCollider->GetObjName() == L"��")
	{

		m_Gravity = false;
	}
}

void CLightMonster::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�Ա�")
	{
		Logger::Debug(L"���Ͱ� ���������ֽ��ϴ�.");
	}
	if (pOtherCollider->GetObjName() == L"��")
	{

		m_Gravity = false;
	}
}

void CLightMonster::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�Ա�")
	{
		Logger::Debug(L"���͸� �Ծ����ϴ�.");
		DELETEOBJECT(this);

	}
}
