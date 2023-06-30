#include "framework.h"
#include "CItem.h"
#include "CCollider.h"
#include "CEventManager.h"
#include "CKirby.h"

CItem::CItem()
{
	m_vecScale = Vector(10, 10);
	m_layer = Layer::Item;
	m_strName = L"¾ÆÀÌÅÛ";
	ItemGetSound = RESOURCE->LoadSound(L"ItemGetSound", L"Sound\\ItemGet.wav");
	HealHpSound = RESOURCE->LoadSound(L"HealHPSound", L"Sound\\HealHP.wav");
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
		SOUND->Play(ItemGetSound, 0.1f, false);
		DELETEOBJECT(this);
	}
}
