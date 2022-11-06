#include "framework.h"
#include "CMonster.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CPlayer.h"

CMonster::CMonster()
{
	m_strName = L"몬스터";
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
	m_vecPos += m_vecDir * m_fVelocity * DT;


	
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
	
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		Logger::Debug(L"몬스터가 플레이어와 상호작용 하여 사라집니다.");
		DELETEOBJECT(this);
	}

	if (pOtherCollider->GetObjName() == L"먹기")
	{
		Logger::Debug(L"몬스터가 빨려가기 시작합니다.");
		
	}
	SetDir(Vector(-1, 0));
}

void CMonster::OnCollisionStay(CCollider* pOtherCollider)
{

	if (pOtherCollider->GetObjName() == L"먹기")
	{
		Logger::Debug(L"몬스터가 빨려들어가고있습니다.");
		
	}
	SetDir(Vector(-2, 0));
}

void CMonster::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"먹기")
	{
		Logger::Debug(L"몬스터를 먹었습니다.");
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
