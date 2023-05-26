#include "framework.h"
#include "CGroundTile.h"

#include "CResourceManager.h"
#include "CRenderManager.h"
#include "CCollider.h"
#include "CNomalKirby.h"

CGroundTile::CGroundTile()
{
	m_strName = L"�ٴ�";
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
	// ��Ÿ�ϰ� �浹���� ��� ó��
	if (pOther->GetOwner()->GetName() == L"Ŀ��")
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

	if (pOther->GetOwner()->GetName() == L"����")
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
	// ��Ÿ�ϰ� �浹���� ��� ó��
}

void CGroundTile::OnCollisionExit(CCollider* pOther)
{
	// ��Ÿ�ϰ� �浹���� ��� ó��
}
