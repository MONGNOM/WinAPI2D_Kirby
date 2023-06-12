#include "framework.h"
#include "CMeat.h"

CMeat::CMeat()
{
	image = nullptr;
}

CMeat::~CMeat()
{
}

void CMeat::Init()
{
	image = RESOURCE->LoadImg(L"Meat", L"Image\\Meat.png");
	AddCollider(ColliderType::Rect, Vector(30, 30), Vector(15, 15));
}

void CMeat::Update()
{
}

void CMeat::Render()
{
	RENDER->Image(image,
		m_vecPos.x,
		m_vecPos.y,
		m_vecPos.x + (float)image->GetWidth(),
		m_vecPos.y + (float)image->GetHeight()
	);
}

void CMeat::Release()
{
}
