#include "framework.h"
#include "BossMakeStar.h"
#include "CNomalKirby.h"

BossMakeStar::BossMakeStar()
{
	m_pAnimator = nullptr;
	m_pstarImage = nullptr;
	effect = nullptr;
	m_layer = Layer::Star;
}	

BossMakeStar::~BossMakeStar()
{
}

void BossMakeStar::Init()
{
	m_pstarImage = RESOURCE->LoadImg(L"BossStar", L"Image\\BossMakeStar.png");
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"bossstar", m_pstarImage, Vector(0.f, 0.f), Vector(70.f, 70.f), Vector(70.5f, 0.f), 0.03f, 6);

	m_pAnimator->Play(L"bossstar", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(50, 50), Vector(0, 0));
}

void BossMakeStar::Update()
{
	starTimer += DT;
	if (starTimer > 3.0f)
	{
		DELETEOBJECT(this);
	}
}

void BossMakeStar::Render()
{
}

void BossMakeStar::Release()
{
}


void BossMakeStar::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"일반커비")
	{
		CNomalKirby* normalKirby = (CNomalKirby*)pOtherCollider->GetOwner();
		if (normalKirby->eat)
		{
			normalKirby->eating = true;
			DELETEOBJECT(this);
		}
	}
}

void BossMakeStar::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Eat)
	{
		if (m_vecPos.x > pOtherCollider->GetOwner()->GetPos().x)
			m_vecPos.x -= 500 * DT;
		if (m_vecPos.x < pOtherCollider->GetOwner()->GetPos().x)
			m_vecPos.x += 500 * DT;
	}
}


