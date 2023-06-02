#include "framework.h"
#include "CItem.h"
#include "CCollider.h"
#include "CEventManager.h"

CItem::CItem()
{
	m_vecScale = Vector(10, 10);
	m_layer = Layer::Item;
	m_strName = L"아이템";
}

CItem::~CItem()
{
}

void CItem::Init()
{
	AddCollider(ColliderType::Rect, Vector(10, 10), Vector(0, 0));
}

void CItem::Update()
{
}

void CItem::Render()
{
}

void CItem::Release()
{
}

void CItem::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Player)
	{
		DELETEOBJECT(this);
		Logger::Debug(L"아이템을 먹었다");
	}
}
