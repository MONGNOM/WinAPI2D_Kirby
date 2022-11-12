#include "framework.h"
#include "CLightKirby.h"

#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"
#include "CMonster.h"

#include "CMissile.h"
#include "KirbyEat.h"
#include "KirbyShot.h"

CLightKirby::CLightKirby()
{
	ontile = 0;
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::LPlayer;
	m_strName = L"플레이어";

	m_Eat = true;
	m_pIdleImageR = nullptr;
	m_pIdleImageD = nullptr;
	m_pIdleImageU = nullptr;
	m_pIdleImageL = nullptr;
	m_pMoveImage = nullptr;
	m_pAttackImage = nullptr;

	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_bIsMove = false;
	Jumpgo = false;
	JumpTime = 0.f;
	m_Basic = true;

	m_LightChange = false;
	LastJumpTime = 0.f;
	LastRunTime;
	m_Gravity = true;
	m_pChangeImage = nullptr;
}

CLightKirby::~CLightKirby()
{
}

void CLightKirby::Init()
{

	m_pChangeImage = RESOURCE->LoadImg(L"PlayerChange", L"Image\\SparkKirby2.png");




	m_pAnimator = new CAnimator;

	m_pAnimator->CreateAnimation(L"IdleUpChange", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);
	m_pAnimator->CreateAnimation(L"IdleRightChange", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);
	m_pAnimator->CreateAnimation(L"IdleDownChange", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);
	m_pAnimator->CreateAnimation(L"IdleLeftChange", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);


	m_pAnimator->CreateAnimation(L"MoveUpChange", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);
	m_pAnimator->CreateAnimation(L"MoveRightChange", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);
	m_pAnimator->CreateAnimation(L"MoveDownChange", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);
	m_pAnimator->CreateAnimation(L"MoveLeftChange", m_pChangeImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);



	m_pAnimator->Play(L"IdleUpChange", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(50, 55), Vector(0, 20));



}

void CLightKirby::Update()
{

}

void CLightKirby::Render()
{
}

void CLightKirby::Release()
{
}

void CLightKirby::LightChange()
{
}

void CLightKirby::Gravity()
{
}

void CLightKirby::Eat()
{
}

void CLightKirby::AnimatorUpdate()
{
}

void CLightKirby::Shot()
{
}

void CLightKirby::OnCollisionEnter(CCollider* pOtherCollider)
{
}

void CLightKirby::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CLightKirby::OnCollisionExit(CCollider* pOtherCollider)
{
}
