#include "framework.h"
#include "CKirby.h"
CKirby::CKirby()
{
}

CKirby::~CKirby()
{
}

void CKirby::Init()
{
}

void CKirby::Update()
{
	m_jumpSpeed -= m_gravity * DT;
	fallTimer += DT;
	lastLeftInputTime += DT;
	lastRightInputTime += DT;
	m_vecLookDir = m_vecMoveDir;
}

void CKirby::Render()
{
}

void CKirby::Release()
{
}

void CKirby::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"¹Ù´Ú")
	{
		m_groundCounter++;
		m_groundchecker = true;
	}
}

void CKirby::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CKirby::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"¹Ù´Ú")
	{
		--m_groundCounter;
		if (m_groundCounter <= 0)
		{
			m_groundchecker = false;
		}
	}
}
