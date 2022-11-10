#include "framework.h"
#include "CBlock.h"

#include "CResourceManager.h"
#include "CRenderManager.h"
#include "CCollider.h"
#include "CTile.h"
#include "CPlayer.h"

CBlock::CBlock()
{
	m_strName = L"��";
	m_type = TypeTile::Wall;
	
}

CBlock::~CBlock()
{
}

void CBlock::Init()
{
	CTile::Init();

	AddCollider(ColliderType::Rect,
		Vector(CTile::TILESIZE, CTile::TILESIZE),
		Vector(CTile::TILESIZE / 2, CTile::TILESIZE / 2));
}

void CBlock::Update()
{
	CTile::Update();
}

void CBlock::Render()
{
	CTile::Render();

	ComponentRender();
}

void CBlock::Release()
{
	CTile::Release();

}

void CBlock::OnCollisionEnter(CCollider* pOther)
{
	if (pOther->GetObjName() == L"�÷��̾�")
	{

		Logger::Debug(L"�÷��̾ ���� �ε��� �з����ϴ�");
	
		//���� �����̸� �浹�� �������� �б� && �ݴ���⵵ ��������
		CGameObject* pl = pOther->GetOwner();
		if (GetTilePosX() <= pl->GetPos().x)
			pl->SetPos(pl->GetPos().x + 5, pl->GetPos().y);
		else
			pl->SetPos(pl->GetPos().x - 5, pl->GetPos().y);

		 
	}
}

void CBlock::OnCollisionStay(CCollider* pOther)
{
	if (pOther->GetObjName() == L"�÷��̾�")
	{

		Logger::Debug(L"�÷��̾ ���� �ε��� �з����ϴ�");

		//���� �����̸� �浹�� �������� �б� && �ݴ���⵵ ��������
		CGameObject* pl = pOther->GetOwner();
		if (GetTilePosX() <= pl->GetPos().x)
			pl->SetPos(pl->GetPos().x + 5, pl->GetPos().y);
		else
			pl->SetPos(pl->GetPos().x - 5, pl->GetPos().y);


	}
}

void CBlock::OnCollisionExit(CCollider* pOther)
{
	/*if (pOther->GetObjName() == L"�÷��̾�")
	{
		CGameObject* pl = pOther->GetOwner();
		pl->SetPos(pl->GetPos().x - 1, pl->GetPos().y);
		 ���� �����̸� �浹�� �������� �б� && �ݴ���⵵ ��������
		if (GetTilePosX() <= pl->GetPos().x)
			pl->GetPos().x + 1;
		else if (GetTilePosX() >= pl->GetPos().x)
			pl->GetPos().x - 1;

	}*/
}
