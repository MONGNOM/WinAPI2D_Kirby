#include "framework.h"
#include "CWallTile.h"

#include "CResourceManager.h"
#include "CRenderManager.h"
#include "CCollider.h"
#include "CPlayer.h"

CWallTile::CWallTile()
{
	m_vecScale = Vector(64, 80);
	m_layer = Layer::Wall;
	m_colDir = CollisionDir::None;
	m_offSet = 0.25f;
}

CWallTile::~CWallTile()
{
}

void CWallTile::Init()
{
	CTile::Init();

	AddCollider(ColliderType::Rect,
		Vector(CTile::TILESIZE, CTile::TILESIZE),
		Vector(CTile::TILESIZE / 2, CTile::TILESIZE / 2));
}

void CWallTile::Update()
{
	CTile::Update();
}

void CWallTile::Render()
{
	CTile::Render();

	ComponentRender();
}

void CWallTile::Release()
{
	CTile::Release();
}

void CWallTile::OnCollisionEnter(CCollider* pOther)
{
	// 땅타일과 충돌했을 경우 처리
}

void CWallTile::OnCollisionStay(CCollider* pOther)
{
	// 땅타일과 충돌했을 경우 처리
	if (pOther->GetOwner()->GetLayer() == Layer::Player || pOther->GetOwner()->GetLayer() == Layer::Monster || pOther->GetOwner()->GetLayer() == Layer::ChangeFormStar)
	{
		// 플레이어가 충돌 중일 경우 밀어내기 연산
		CPlayer* pPlayer = static_cast<CPlayer*>(pOther->GetOwner());

		m_colDir = GetCollisionDir(pOther);

		switch (GetCollisionDir(pOther))
		{
		case CollisionDir::Up:
		{
			pPlayer->SetPos(
				pPlayer->GetPos().x,
				GetCollider()->GetPos().y
				- (GetCollider()->GetScale().y + pOther->GetScale().y) * 0.5f + m_offSet
				- pOther->GetOffsetPos().y
			);
		}
		break;

		case CollisionDir::Down:
		{
			pPlayer->SetPos(
				pPlayer->GetPos().x,
				GetCollider()->GetPos().y
				+ (GetCollider()->GetScale().y + pOther->GetScale().y) * 0.5f - m_offSet
				- pOther->GetOffsetPos().y
			);
		}
		break;

		case CollisionDir::Left:
		{
			pPlayer->SetPos(
				GetCollider()->GetPos().x
				- (GetCollider()->GetScale().x + pOther->GetScale().x) * 0.5f + m_offSet
				- pOther->GetOffsetPos().x,
				pPlayer->GetPos().y
			);
		}
		break;

		case CollisionDir::Right:
		{
			pPlayer->SetPos(
				GetCollider()->GetPos().x
				+ (GetCollider()->GetScale().x + pOther->GetScale().x) * 0.5f - m_offSet
				- pOther->GetOffsetPos().x,
				pPlayer->GetPos().y
			);
		}
		break;
		}
	}
}

void CWallTile::OnCollisionExit(CCollider* pOther)
{
	// 땅타일과 충돌했을 경우 처리
}

CollisionDir CWallTile::GetCollisionDir(CCollider* pOther)
{
	ColliderInfo obj = ColliderInfo(GetCollider()->GetPos(), GetCollider()->GetScale());
	ColliderInfo other = ColliderInfo(pOther->GetPos(), pOther->GetScale());

	if (((obj.scale.x + other.scale.x) * 0.5f - abs(obj.pos.x - other.pos.x) < m_offSet * 4
		&& ((obj.scale.y + other.scale.y) * 0.5f - abs(obj.pos.y - other.pos.y)) < m_offSet * 4))
	{
		return CollisionDir::None;
	}
	else if (((obj.scale.x + other.scale.x) * 0.5f - abs(obj.pos.x - other.pos.x))
		< (obj.scale.y + other.scale.y) * 0.5f - abs(obj.pos.y - other.pos.y))
	{
		if (obj.pos.x > other.pos.x && obj.left < other.right - m_offSet)
			return CollisionDir::Left;
		if (obj.pos.x < other.pos.x && obj.right > other.left + m_offSet)
			return CollisionDir::Right;
	}
	else
	{
		if (obj.pos.y > other.pos.y && obj.up < other.down - m_offSet)
			return CollisionDir::Up;
		if (obj.pos.y < other.pos.y && obj.down > other.up + m_offSet)
			return CollisionDir::Down;
	}

	return CollisionDir::None;
}
