#include "framework.h"
#include "CKirbyShot.h"
#include "CNomalKirby.h"

CKirbyShot::CKirbyShot(Vector dir)
{
	m_pAnimator = nullptr;
	m_pAttackImage = nullptr;
	m_vecLookDir = dir;
}

CKirbyShot::~CKirbyShot()
{
}

void CKirbyShot::Init()
{
	m_pAttackImage = RESOURCE->LoadImg(L"KirbyShot", L"Image\\ShotEffect1.png");
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"AttackR", m_pAttackImage, Vector(0.f, 0.f), Vector(75.f, 79.f), Vector(78.f, 0.f), 0.02f, 8);

	m_pAnimator->Play(L"AttackR", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(40, 40), Vector(0, 0));
}

void CKirbyShot::Update()
{
	m_vecPos += m_vecLookDir * 300 * DT;
}

void CKirbyShot::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Monster || pOtherCollider->GetOwner()->GetLayer() == Layer::Tile)
	{
		effect = new CEffect();
		effect->effectDestory = true;
		effect->SetPos(m_vecPos);
		ADDOBJECT(effect);
		effect->NomalAttackDestoryEffect();
		DELETEOBJECT(this);
	}
}
