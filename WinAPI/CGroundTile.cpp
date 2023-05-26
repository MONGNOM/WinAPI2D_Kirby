#include "framework.h"
#include "CGroundTile.h"

#include "CResourceManager.h"
#include "CRenderManager.h"
#include "CCollider.h"
#include "CNomalKirby.h"

CGroundTile::CGroundTile()
{
	m_strName = L"바닥";
}

CGroundTile::~CGroundTile()
{
}

void CGroundTile::Init()
{
	CTile::Init();

	AddCollider(ColliderType::Rect,
		Vector(CTile::TILESIZE, CTile::TILESIZE),
		Vector(CTile::TILESIZE / 2, CTile::TILESIZE / 2));
}

void CGroundTile::Update()
{
	CTile::Update();
}

void CGroundTile::Render()
{
	CTile::Render();

	ComponentRender();
}

void CGroundTile::Release()
{
	CTile::Release();
}

void CGroundTile::OnCollisionEnter(CCollider* pOther)
{
	// 땅타일과 충돌했을 경우 처리
	if (pOther->GetOwner()->GetName() == L"커비")
	{
		CGameObject* pPlayer = pOther->GetOwner();
		if (pPlayer->GetPos().y < m_vecPos.y)
		{
			pPlayer->SetPos(Vector(pPlayer->GetPos().x, pPlayer->GetPos().y - 0.5f));
		}
		else if (pPlayer->GetPos().y > m_vecPos.y)
		{
			pPlayer->SetPos(Vector(pPlayer->GetPos().x, pPlayer->GetPos().y + 0.5f));
		}

		if (pPlayer->GetPos().x >= m_vecPos.x && pPlayer->GetPos().y >= m_vecPos.y)
		{
			pPlayer->SetPos(Vector(pPlayer->GetPos().x + 2, pPlayer->GetPos().y));
		}
		else if (pPlayer->GetPos().x <= m_vecPos.x && pPlayer->GetPos().y >= m_vecPos.y)
		{
			pPlayer->SetPos(Vector(pPlayer->GetPos().x - 2, pPlayer->GetPos().y));
		}
	}

	if (pOther->GetOwner()->GetName() == L"몬스터")
	{
		CGameObject* pPlayer = pOther->GetOwner();
		if (pPlayer->GetPos().y < m_vecPos.y)
		{
			pPlayer->SetPos(Vector(pPlayer->GetPos().x, pPlayer->GetPos().y - 0.5f));
		}
		else if (pPlayer->GetPos().y > m_vecPos.y)
		{
			pPlayer->SetPos(Vector(pPlayer->GetPos().x, pPlayer->GetPos().y + 0.5f));
		}

		if (pPlayer->GetPos().x >= m_vecPos.x && pPlayer->GetPos().y >= m_vecPos.y)
		{
			pPlayer->SetPos(Vector(pPlayer->GetPos().x + 2, pPlayer->GetPos().y));
		}
		else if (pPlayer->GetPos().x <= m_vecPos.x && pPlayer->GetPos().y >= m_vecPos.y)
		{
			pPlayer->SetPos(Vector(pPlayer->GetPos().x - 2, pPlayer->GetPos().y));
		}
	}

}

void CGroundTile::OnCollisionStay(CCollider* pOther)
{
	// 땅타일과 충돌했을 경우 처리
}

void CGroundTile::OnCollisionExit(CCollider* pOther)
{
	// 땅타일과 충돌했을 경우 처리
}
