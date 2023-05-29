#include "framework.h"
#include "CSword.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CRenderManager.h"
#include "CCollisionManager.h"

CSword::CSword()
{
	damage = 2;
}

CSword::~CSword()
{
}

void CSword::Init()
{
	AddCollider(ColliderType::Rect, Vector(90, 100), Vector(0, 0));
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
