#include "framework.h"
#include "CKirbyHp.h"

#include "CPlayer.h"

CKirbyHp::CKirbyHp()
{
}

CKirbyHp::~CKirbyHp()
{
}

void CKirbyHp::SetHp()
{
	GAME->PlayerHp;
}

void CKirbyHp::OnMouseEnter()
{
}

void CKirbyHp::OnMouseOver()
{
}

void CKirbyHp::OnMouseExit()
{
}

void CKirbyHp::OnMouseUp()
{
}

void CKirbyHp::OnMouseDown()
{
}

void CKirbyHp::OnMouseClicked()
{
}

void CKirbyHp::Init()
{

	HpImage = RESOURCE->LoadImg(L"PlayerHP", L"Image\\KirbyHp.png");
	m_bScreenFixed = true;
}

void CKirbyHp::Update()
{
}

void CKirbyHp::Render()
{
	if (GAME->PlayerHp == 5)
		RENDER->Image(HpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 180, m_vecRenderPos.y + 50);
	else if (GAME->PlayerHp == 4)
	{
		RENDER->Image(HpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 180, m_vecRenderPos.y + 50);
		RENDER->FillRect(m_vecRenderPos.x + 166.5, m_vecRenderPos.y + 10.8, m_vecRenderPos.x + 133, m_vecRenderPos.y + 40);
	}
	else if (GAME->PlayerHp == 3)
	{
		RENDER->Image(HpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 180, m_vecRenderPos.y + 50);
		RENDER->FillRect(m_vecRenderPos.x + 166.5, m_vecRenderPos.y + 10.8, m_vecRenderPos.x + 103, m_vecRenderPos.y + 40);
	}
	else if (GAME->PlayerHp == 2)
	{
	RENDER->Image(HpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 180, m_vecRenderPos.y + 50);
	RENDER->FillRect(m_vecRenderPos.x + 166.5, m_vecRenderPos.y + 10.8, m_vecRenderPos.x + 73, m_vecRenderPos.y + 40);
	}
	else if (GAME->PlayerHp == 1)
	{
		RENDER->Image(HpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 180, m_vecRenderPos.y + 50);
		RENDER->FillRect(m_vecRenderPos.x + 166.5, m_vecRenderPos.y + 10.8, m_vecRenderPos.x + 43, m_vecRenderPos.y + 40);
	}
	else if (GAME->PlayerHp == 0)
	{
		RENDER->Image(HpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 180, m_vecRenderPos.y + 50);
		RENDER->FillRect(m_vecRenderPos.x + 166.5, m_vecRenderPos.y + 10.8, m_vecRenderPos.x + 13, m_vecRenderPos.y + 40);

	}
}

void CKirbyHp::Release()
{
}
