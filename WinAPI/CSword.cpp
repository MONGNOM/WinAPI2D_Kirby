#include "framework.h"
#include "CSword.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CRenderManager.h"
#include "CCollisionManager.h"
#include "CCollider.h"

CSword::CSword()
{
	damage = 2;
}

CSword::~CSword()
{
}

void CSword::Init()
{
	AddCollider(ColliderType::Rect, m_vecScale, Vector(0, 0));
}

void CSword::Update()
{
	CKirbyWeapon::Update();
}

void CSword::Render()
{
}

void CSword::Release()
{
}

void CSword::SetColliderSize(Vector scale, Vector offsetPos)
{
	this->m_vecScale = scale;
	SetCollider(scale, offsetPos);
}
