#include "framework.h"
#include "CMonster.h"

#include "CRenderManager.h"
#include "CCollider.h"

CMonster::CMonster()
{
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Monster;
	m_fSpeed = 0.f;
	m_vecLookDir = Vector(1, 0);
	m_groundchecker = false;
	m_groundCounter = 0;
	m_gravity = 300;
	dieTime = 0;
	hp = 10;
}

CMonster::~CMonster()
{
}

void CMonster::Init()
{
	AddCollider(ColliderType::Rect, Vector(50, 50), Vector(0, 0));
}

void CMonster::Update()
{
	
}

void CMonster::Render()
{
	
}

void CMonster::Release()
{
}

void CMonster::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�ٴ�")
	{
		m_groundCounter++;
		m_groundchecker = true;
		Logger::Debug(L"���Ͱ� �ٴڰ� �ε���");
	}

	if (pOtherCollider->GetObjName() == L"Ŀ��")
	{
		--hp;
		Logger::Debug(L"Ŀ��� �浹");
	}
}

void CMonster::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CMonster::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�ٴ�")
	{
		--m_groundCounter;
		if (m_groundCounter <= 0)
		{
			m_groundchecker = false;
			Logger::Debug(L"���Ͱ� �̻��ϰ� �浹����");
		}
	}
}
