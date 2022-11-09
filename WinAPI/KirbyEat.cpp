#include "framework.h"
#include "KirbyEat.h"

#include "CPlayer.h"

KirbyEat::KirbyEat()
{

	m_vecPos = Vector( 0, 0);
	m_vecScale = Vector(0, 0);
	m_layer = Layer::Eat;
	m_strName = L"먹기";
	m_vecDir = Vector(0, 0);

}

KirbyEat::~KirbyEat()
{
}

void KirbyEat::Init()
{
	AddCollider(ColliderType::Rect, Vector(100, 100), Vector(0, 0));

}

void KirbyEat::Update()
{
	if (BUTTONUP('S'))
	{
		DELETEOBJECT(this);

	}
}

void KirbyEat::Render()
{
}

void KirbyEat::Release()
{
}

void KirbyEat::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}


void KirbyEat::OnCollisionEnter(CCollider* pOtherCollider)
{

}




void KirbyEat::OnCollisionStay(CCollider* pOtherCollider)
{
}

void KirbyEat::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"몬스터")
	{
		
		Logger::Debug(L"몬스터를 먹었습니다.");
	}
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		CGameObject* pl = pOtherCollider->GetOwner();
	}
}
