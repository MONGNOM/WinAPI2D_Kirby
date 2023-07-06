#include "framework.h"
#include "CBossDoor.h"
#include "CSceneManager.h"
#include "CInputManager.h"
#include "CImageObject.h"
#include "CResourceManager.h"
#include "CResource.h"



CBossDoor::CBossDoor()
{
	m_layer = Layer::Door;
	m_pAnimator = nullptr;
	m_DoorImage = nullptr;
	door = false;
}

CBossDoor::~CBossDoor()
{
}

void CBossDoor::Init()
{
	m_DoorImage = RESOURCE->LoadImg(L"DoorEffect", L"Image\\StarEffect.png");
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Star", m_DoorImage, Vector(0.f, 0.f), Vector(75.f, 79.f), Vector(78.f, 0.f), 0.05f, 8);

	m_pAnimator->Play(L"Star", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(70, 90), Vector(0, 55));
}

void CBossDoor::Update()
{
	if (BUTTONDOWN(VK_UP) && door == true)
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Stage02, 0.25f);
	}
}

void CBossDoor::Render()
{
	RENDER->FillRect(m_vecPos.x - 35, m_vecPos.y + 10, m_vecPos.x + 35, m_vecPos.y + 100);
}

void CBossDoor::Release()
{
}

void CBossDoor::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Player)
	{
		door = true;
	}
}

void CBossDoor::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CBossDoor::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Player)
	{
		door = false;
	}
}
