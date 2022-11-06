#include "framework.h"
#include "KirbyEat.h"

KirbyEat::KirbyEat()
{
	
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(0, 0);
	m_layer = Layer::Eat;
	m_strName = L"¸Ô±â";
}

KirbyEat::~KirbyEat()
{
}

void KirbyEat::Init()
{
	AddCollider(ColliderType::Rect, Vector(100, 100), Vector(50, 0));

}

void KirbyEat::Update()
{
}

void KirbyEat::Render()
{
	RENDER->FrameRect(
		m_vecPos.x + 50 - m_vecScale.x*5,
		m_vecPos.y		- m_vecScale.y*5,
		m_vecPos.x +50	+ m_vecScale.x*5,
		m_vecPos.y		+ m_vecScale.y *5);
}

void KirbyEat::Release()
{
}

void KirbyEat::OnCollisionEnter(CCollider* pOtherCollider)
{
}

void KirbyEat::OnCollisionStay(CCollider* pOtherCollider)
{
	
}

void KirbyEat::OnCollisionExit(CCollider* pOtherCollider)
{

}
