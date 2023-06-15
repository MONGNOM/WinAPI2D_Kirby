#include "framework.h"
#include "CMeat.h"
#include "CKirby.h"
#include "CGameManager.h"

CMeat::CMeat()
{
	image = nullptr;
}

CMeat::~CMeat()
{
}

void CMeat::Init()
{
	image = RESOURCE->LoadImg(L"Meat", L"Image\\Meat.png");
	AddCollider(ColliderType::Rect, Vector(30, 30), Vector(15, 15));
}

void CMeat::Update()
{
}

void CMeat::Render()
{
	RENDER->Image(image,
		m_vecPos.x,
		m_vecPos.y,
		m_vecPos.x + (float)image->GetWidth(),
		m_vecPos.y + (float)image->GetHeight()
	);
}

void CMeat::Release()
{
}

void CMeat::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Player)
	{
		CKirby* Kirby = (CKirby*)pOtherCollider->GetOwner();
		if (Kirby->playerHp += GAME->maxHp * 0.5 > 5)
			Kirby->playerHp = GAME->maxHp;
		else
			Kirby->playerHp += GAME->maxHp  * 0.5;
		DELETEOBJECT(this);
		Logger::Debug(L"아이템을 먹었다");
	}
}
