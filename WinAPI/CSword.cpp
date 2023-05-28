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
	AddCollider(ColliderType::Rect, Vector(70, 60), Vector(0, 0));
}

void CSword::Update()
{
	/*if (BUTTONUP('S'))
	{
		DELETEOBJECT(this);
	}*/
}

void CSword::Render()
{
	//RENDER->FillRect(10, 10, 10, 10);
}

void CSword::Release()
{
}
