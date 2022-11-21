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
	m_layer = Layer::Tile;
	
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
		if (GetTilePosX() >= GAME->PlayerPos.x)
			pl->SetPos(GAME->PlayerPos.x + 5, GAME->PlayerPos.y);
		else
			pl->SetPos(GAME->PlayerPos.x - 5, GAME->PlayerPos.y);
	}

	if (pOther->GetObjName() == L"����")
	{

		Logger::Debug(L"�÷��̾ ���� �ε��� �з����ϴ�");

		//���� �����̸� �浹�� �������� �б� && �ݴ���⵵ ��������
		CGameObject* pl1 = pOther->GetOwner();
		if (GetTilePosX() >= pl1->GetPos().x)
			pl1->SetPos(pl1->GetPos().x + 5, pl1->GetPos().y);
		else
			pl1->SetPos(pl1->GetPos().x - 5, pl1->GetPos().y);
	}

	if (pOther->GetObjName() == L"���� ����")
	{

		Logger::Debug(L"�÷��̾ ���� �ε��� �з����ϴ�");

		//���� �����̸� �浹�� �������� �б� && �ݴ���⵵ ��������
		CGameObject* pl1 = pOther->GetOwner();
		if (GetTilePosX() >= pl1->GetPos().x)
			pl1->SetPos(pl1->GetPos().x + 5, pl1->GetPos().y);
		else
			pl1->SetPos(pl1->GetPos().x - 5, pl1->GetPos().y);
	}
	
	if (pOther->GetObjName() == L"������")
	{

		Logger::Debug(L"�÷��̾ ���� �ε��� �з����ϴ�");

		//���� �����̸� �浹�� �������� �б� && �ݴ���⵵ ��������
		CGameObject* pl1 = pOther->GetOwner();
		if (GetTilePosX() >= pl1->GetPos().x)
			pl1->SetPos(pl1->GetPos().x + 5, pl1->GetPos().y);
		else
			pl1->SetPos(pl1->GetPos().x - 5, pl1->GetPos().y);
	}

	if (pOther->GetObjName() == L"���� ����")
	{

		Logger::Debug(L"�÷��̾ ���� �ε��� �з����ϴ�");

		//���� �����̸� �浹�� �������� �б� && �ݴ���⵵ ��������
		CGameObject* pl1 = pOther->GetOwner();
		if (GetTilePosX() >= pl1->GetPos().x)
			pl1->SetPos(pl1->GetPos().x + 5, pl1->GetPos().y);
		else
			pl1->SetPos(pl1->GetPos().x - 5, pl1->GetPos().y);
	}
}

void CBlock::OnCollisionStay(CCollider* pOther)
{
	if (pOther->GetObjName() == L"�÷��̾�")
	{

		Logger::Debug(L"�÷��̾ ���� �ε��� �з����ϴ�");

		//���� �����̸� �浹�� �������� �б� && �ݴ���⵵ ��������
		CGameObject* pl = pOther->GetOwner();
		if (GetTilePosX() >= GAME->PlayerPos.x)
			pl->SetPos(GAME->PlayerPos.x - 5, GAME->PlayerPos.y);
		else
			pl->SetPos(GAME->PlayerPos.x + 5, GAME->PlayerPos.y);
	}

	if (pOther->GetObjName() == L"����")
	{

		Logger::Debug(L"�÷��̾ ���� �ε��� �з����ϴ�");

		//���� �����̸� �浹�� �������� �б� && �ݴ���⵵ ��������
		CGameObject* pl12 = pOther->GetOwner();
		if (GetTilePosX() >= pl12->GetPos().x)
			pl12->SetPos(pl12->GetPos().x - 5, pl12->GetPos().y);
		else
			pl12->SetPos(pl12->GetPos().x + 5, pl12->GetPos().y);
	}

	if (pOther->GetObjName() == L"���� ����")
	{

		Logger::Debug(L"�÷��̾ ���� �ε��� �з����ϴ�");

		//���� �����̸� �浹�� �������� �б� && �ݴ���⵵ ��������
		CGameObject* pl12 = pOther->GetOwner();
		if (GetTilePosX() >= pl12->GetPos().x)
			pl12->SetPos(pl12->GetPos().x - 5, pl12->GetPos().y);
		else
			pl12->SetPos(pl12->GetPos().x + 5, pl12->GetPos().y);
	}

	if (pOther->GetObjName() == L"������")
	{

		Logger::Debug(L"�÷��̾ ���� �ε��� �з����ϴ�");

		//���� �����̸� �浹�� �������� �б� && �ݴ���⵵ ��������
		CGameObject* pl12 = pOther->GetOwner();
		if (GetTilePosX() >= pl12->GetPos().x)
			pl12->SetPos(pl12->GetPos().x - 5, pl12->GetPos().y);
		else
			pl12->SetPos(pl12->GetPos().x + 5, pl12->GetPos().y);
	}
	
	if (pOther->GetObjName() == L"���� ����")
	{

		Logger::Debug(L"�÷��̾ ���� �ε��� �з����ϴ�");

		//���� �����̸� �浹�� �������� �б� && �ݴ���⵵ ��������
		CGameObject* pl12 = pOther->GetOwner();
		if (GetTilePosX() >= pl12->GetPos().x)
			pl12->SetPos(pl12->GetPos().x - 5, pl12->GetPos().y);
		else
			pl12->SetPos(pl12->GetPos().x + 5, pl12->GetPos().y);
	}
}

void CBlock::OnCollisionExit(CCollider* pOther)
{
	
}
