#include "framework.h"
#include "CKirbyHp.h"
#include "CGameManager.h"

CKirbyHp::CKirbyHp()
{
	hpImage = nullptr;
}

CKirbyHp::~CKirbyHp()
{
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
	hpImage = RESOURCE->LoadImg(L"KirbyHP", L"Image\\KirbyHp.png");
}

void CKirbyHp::Update()
{
}

void CKirbyHp::Render()
{
	if (GAME->curHp == 5)
		RENDER->Image(hpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 180, m_vecRenderPos.y + 50);
	else if (GAME->curHp == 4)
	{
		RENDER->Image(hpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 180, m_vecRenderPos.y + 50);
		RENDER->FillRect(m_vecRenderPos.x + 166.5f, m_vecRenderPos.y + 10.8f, m_vecRenderPos.x + 133, m_vecRenderPos.y + 40);
	}
	else if (GAME->curHp == 3)
	{
		RENDER->Image(hpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 180, m_vecRenderPos.y + 50);
		RENDER->FillRect(m_vecRenderPos.x + 166.5f, m_vecRenderPos.y + 10.8f, m_vecRenderPos.x + 103, m_vecRenderPos.y + 40);
	}
	else if (GAME->curHp == 2)
	{
		RENDER->Image(hpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 180, m_vecRenderPos.y + 50);
		RENDER->FillRect(m_vecRenderPos.x + 166.5f, m_vecRenderPos.y + 10.8f, m_vecRenderPos.x + 73, m_vecRenderPos.y + 40);
	}
	else if (GAME->curHp == 1)
	{
		RENDER->Image(hpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 180, m_vecRenderPos.y + 50);
		RENDER->FillRect(m_vecRenderPos.x + 166.5f, m_vecRenderPos.y + 10.8f, m_vecRenderPos.x + 43, m_vecRenderPos.y + 40);
	}
	else if (GAME->curHp == 0)
	{
		RENDER->Image(hpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 180, m_vecRenderPos.y + 50);
		RENDER->FillRect(m_vecRenderPos.x + 166.5f, m_vecRenderPos.y + 10.8f, m_vecRenderPos.x + 13, m_vecRenderPos.y + 40);

	}
}

void CKirbyHp::Release()
{
}
