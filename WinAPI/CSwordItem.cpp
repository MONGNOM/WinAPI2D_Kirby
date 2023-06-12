#include "framework.h"
#include "CSwordItem.h"

CSwordItem::CSwordItem()
{
	m_pAnimator = nullptr;
	m_pSwordItemImage = nullptr;
	m_strName = L"검아이템";

}

CSwordItem::~CSwordItem()
{
}

void CSwordItem::Init()
{
	m_pSwordItemImage = RESOURCE->LoadImg(L"SwordItemImage", L"Image\\Kirby\\SwordKirby\\SwordBubble.png");
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"SwordItem", m_pSwordItemImage, Vector(0.f, 0.f), Vector(62.f, 57.f), Vector(65.f, 0.f), 0.1f, 4, true);

	m_pAnimator->Play(L"SwordItem", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(50, 50), Vector(0, 0));
}


void CSwordItem::Update()
{
}

void CSwordItem::Render()
{
}

void CSwordItem::Release()
{
}
