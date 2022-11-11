#include "framework.h"
#include "CMonster.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CPlayer.h"

CMonster::CMonster()
{
	m_strName = L"����";
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Monster;
	m_vecDir = Vector(0, 0);
	m_fVelocity = 300;
}

CMonster::~CMonster()
{
}

void CMonster::Init()
{
	AddCollider(ColliderType::Rect, Vector(90, 90), Vector(0, 0));
}

void CMonster::Update()
{
	Gravity();

	m_vecPos += m_vecDir * m_fVelocity * DT;


	
}



void CMonster::Gravity()
{
	if (m_Gravity == true)
	{
		m_vecPos.y += m_fSpeed * DT * 2;
	}


}


void CMonster::Render()
{
	RENDER->FrameRect(
		m_vecPos.x - m_vecScale.x * 0.5f,
		m_vecPos.y - m_vecScale.y * 0.5f,
		m_vecPos.x + m_vecScale.x * 0.5f,
		m_vecPos.y + m_vecScale.y * 0.5f);
	
}

void CMonster::Release()
{
}

void CMonster::OnCollisionEnter(CCollider* pOtherCollider)
{
	
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
	{
		Logger::Debug(L"���Ͱ� �÷��̾�� �ε��� �������� �Խ��ϴ�.");
		DELETEOBJECT(this);
	}

	if (pOtherCollider->GetObjName() == L"�Ա�")
	{
		Logger::Debug(L"���Ͱ� �������� �����մϴ�.");
		CGameObject* pl = pOtherCollider->GetOwner();
		if(pl->GetPos().x <= m_vecPos.x )
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

void CMonster::OnCollisionStay(CCollider* pOtherCollider)
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

void CMonster::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�Ա�")
	{
		Logger::Debug(L"���͸� �Ծ����ϴ�.");
		DELETEOBJECT(this);

	}

}

void CMonster::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CMonster::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
