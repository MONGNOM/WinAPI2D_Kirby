#include "framework.h"
#include "CIceAttack.h"
#include "CGameManager.h"

CIceAttack::CIceAttack()
{
	m_pAnimator = nullptr;
	m_pAttackImage = nullptr;
	m_strName = L"¾ó¸®±â";
	m_layer = Layer::Ice;
	damage = 1;
}

CIceAttack::~CIceAttack()
{

}

void CIceAttack::Init()
{
	m_pAttackImage = RESOURCE->LoadImg(L"IceAttackKirby", L"Image\\Effect.png");
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IceAttackL", m_pAttackImage, Vector(0.f, 800.f), Vector(220.f, 100.f), Vector(230.f, 0.f), 0.03f, 12);
	m_pAnimator->CreateAnimation(L"IceAttackR", m_pAttackImage, Vector(2560.f, 900.f), Vector(220.f, 100.f), Vector(-230.f, 0.f), 0.03f, 12);

	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(140, 80), Vector(0, 0));
}
void CIceAttack::Update()
{
	AnimatorUpdate();
}

void CIceAttack::Render()
{
}

void CIceAttack::Release()
{
}

void CIceAttack::Attack()
{
	if (GAME->playerLoockDirX == -1)
	{
		iceAttackstate = L"IceAttackL";

	}
	if (GAME->playerLoockDirX == 1)
	{
		iceAttackstate = L"IceAttackR";
	}
}

void CIceAttack::AnimatorUpdate()
{
	m_pAnimator->Play(iceAttackstate, false);
}
