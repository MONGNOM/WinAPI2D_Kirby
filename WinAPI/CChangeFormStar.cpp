#include "framework.h"
#include "CChangeFormStar.h"
#include "CGameManager.h"
#include "CNomalKirby.h"

CChangeFormStar::CChangeFormStar()
{
	m_pAnimator = nullptr;
	m_pChangeFormStarImage = nullptr;
	m_strName = L"ChangeFormStar";
	m_layer = Layer::ChangeFormStar;
	DeathSound = RESOURCE->LoadSound(L"MonsterDeathSound", L"Sound\\MonsterDeath.wav");
}

CChangeFormStar::~CChangeFormStar()
{
}

void CChangeFormStar::ChangeStarName(wstring Name)
{
	m_strName = Name;
}

void CChangeFormStar::Init()
{
	m_pChangeFormStarImage = RESOURCE->LoadImg(L"changeformstar", L"Image\\StarEffect.png");
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"changeformstar", m_pChangeFormStarImage, Vector(0.f, 0.f), Vector(75.f, 79.f), Vector(78.f, 0.f), 0.05f, 8);

	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(40, 40), Vector(0, 0));
}

void CChangeFormStar::Update()
{
	//속도 조절 중력
	changeFormStar = L"changeformstar";
	m_vecPos.x -= GAME->playerLoockDirX - 0.1f  * DT;
	m_vecPos.y -= GAME->playerPos.y * 0.2f * DT;
	
	AnimatorUpdate();

}

void CChangeFormStar::Render()
{
}

void CChangeFormStar::Release()
{
}

void CChangeFormStar::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"빨아들이기")
	{
		if (m_vecPos.x > pOtherCollider->GetOwner()->GetPos().x)
			m_vecPos.x -= 500 * DT;
		if (m_vecPos.x < pOtherCollider->GetOwner()->GetPos().x)
			m_vecPos.x += 500 * DT;
	}
}

void CChangeFormStar::AnimatorUpdate()
{
	m_pAnimator->Play(changeFormStar, false);
}

void CChangeFormStar::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"일반커비")
	{
		CNomalKirby* normalKirby = (CNomalKirby*)pOtherCollider->GetOwner();
		if (normalKirby->eat)
		{
			if (m_strName == L"얼음별")
			{
				normalKirby->ice = true;
			}
			if (m_strName == L"칼별")
			{
				normalKirby->sword = true;
			}
			SOUND->Play(DeathSound, 0.1f, false);
			normalKirby->eating = true;
			DELETEOBJECT(this);
			normalKirby->eat = false;
		}
	}
}
