#include "framework.h"
#include "CChangeFormStar.h"
#include "CGameManager.h"

CChangeFormStar::CChangeFormStar()
{
	m_pAnimator = nullptr;
	m_pChangeFormStarImage = nullptr;
	m_strName = L"ChangeFormStar";
}

CChangeFormStar::~CChangeFormStar()
{
}

void CChangeFormStar::Init()
{
	m_pChangeFormStarImage = RESOURCE->LoadImg(L"KirbyShot", L"Image\\ShotEffect1.png");
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"AttackR", m_pChangeFormStarImage, Vector(0.f, 0.f), Vector(75.f, 79.f), Vector(78.f, 0.f), 0.02f, 8);

	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(40, 40), Vector(0, 0));
}

void CChangeFormStar::Update()
{
	m_vecPos.x += GAME->playerLoockDirX * -300 * DT;
	m_vecPos.y += GAME->playerPos.y * 300 * DT;
	//중력주기
}

void CChangeFormStar::Render()
{
}

void CChangeFormStar::Release()
{
}

void CChangeFormStar::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"빨아들이기")
	{
		if (m_vecPos.x > pOtherCollider->GetOwner()->GetPos().x)
			m_vecPos.x -= 500 * DT;
		if (m_vecPos.x < pOtherCollider->GetOwner()->GetPos().x)
			m_vecPos.x += 500 * DT;
	}
}
