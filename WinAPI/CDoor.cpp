#include "framework.h"
#include "CDoor.h"
#include "CInputManager.h"
#include "CSceneManager.h"

CDoor::CDoor()
{
	m_layer = Layer::Door;
	m_pAnimator = nullptr;
	m_DoorImage = nullptr;
	door = false;
}

CDoor::~CDoor()
{
}

void CDoor::Init()
{
	m_DoorImage = RESOURCE->LoadImg(L"DoorEffect", L"Image\\StarEffect.png");
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Star", m_DoorImage, Vector(0.f, 0.f), Vector(75.f, 79.f), Vector(78.f, 0.f), 0.05f, 8);

	m_pAnimator->Play(L"Star", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(70, 125), Vector(0, 70));
}

void CDoor::Update()
{
	if (BUTTONDOWN(VK_UP) && door == true)
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Bonus, 0.25f);
	}
}

void CDoor::Render()
{
	RENDER->FillRect(m_vecPos.x -35, m_vecPos.y + 10, m_vecPos.x + 35, m_vecPos.y + 105);

}

void CDoor::Release()
{
}

void CDoor::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Player)
	{
		door = true;
	}

}

void CDoor::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Player)
	{
	}

}

void CDoor::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Player)
	{
		door = false;
	}

}