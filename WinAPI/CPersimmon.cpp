#include "framework.h"
#include "CPersimmon.h"
#include "CImageObject.h"
#include "CEventManager.h"
#include "CKirby.h"
#include "CGameManager.h"

CPersimmon::CPersimmon()
{
	image = nullptr;
}

CPersimmon::~CPersimmon()
{
}

void CPersimmon::Init()
{
	image = RESOURCE->LoadImg(L"Persimmon", L"Image\\Persimmon.png");
	AddCollider(ColliderType::Rect, Vector(30, 30), Vector(15, 15));
}

void CPersimmon::Update()
{
}

void CPersimmon::Render()
{
	RENDER->Image(image,
		m_vecPos.x,
		m_vecPos.y,
		m_vecPos.x + (float)image->GetWidth(),
		m_vecPos.y + (float)image->GetHeight()
	);
}

void CPersimmon::Release()
{
}

void CPersimmon::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Player)
	{
		CKirby* Kirby = (CKirby*)pOtherCollider->GetOwner();
		Kirby->playerHp = GAME->maxHp;
		DELETEOBJECT(this);
		Logger::Debug(L"아이템을 먹었다");
	}
}
