#include "framework.h"
#include "CDoor.h"


#include "CCollider.h"


CDoor::CDoor()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(50, 50);
	m_layer = Layer::Door;
	m_strName = L"문";
	DoorOpen = false;

}

CDoor::~CDoor()
{
}

void CDoor::Init()
{

	m_DoorImage = RESOURCE->LoadImg(L"Door", L"Image\\Door.png");

	AddCollider(ColliderType::Rect, Vector(70, 70), Vector(0, 0));
}

void CDoor::Update()
{
	if (BUTTONDOWN(VK_UP) && DoorOpen == true)
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Boss, 0.25f);
	}

	
}

void CDoor::Render()
{
	RENDER->Image(m_DoorImage, m_vecPos.x - 50, m_vecPos.y -100 , m_vecPos.x + 50, m_vecPos.y - 50);
	RENDER->FillRect(m_vecPos.x-35, m_vecPos.y-50 , m_vecPos.x+35, m_vecPos.y+35);
}

void CDoor::Release()
{
}

void CDoor::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		DoorOpen = true;
	}
}

void CDoor::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		DoorOpen = true;
	}
}

void CDoor::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		DoorOpen = false;
	}
}
