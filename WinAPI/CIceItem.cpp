#include "framework.h"
#include "CIceItem.h"

CIceItem::CIceItem()
{
	m_pAnimator = nullptr;
	m_pIceItemImage = nullptr;
	m_strName = L"얼음아이템";
}

CIceItem::~CIceItem()
{
}

void CIceItem::Init()
{
	m_pIceItemImage = RESOURCE->LoadImg(L"IceItemImage", L"Image\\Kirby\\Ice\\IceBubble.png");
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IceItem", m_pIceItemImage, Vector(0.f, 0.f), Vector(62.f, 57.f), Vector(65.f, 0.f), 0.1f, 4, true);
	
	m_pAnimator->Play(L"IceItem", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(50, 50), Vector(0, 0));
}


void CIceItem::Update()
{
}

void CIceItem::Render()
{
}

void CIceItem::Release()
{
}
