#include "framework.h"
#include "CKirbyIcon.h"
#include "CGameManager.h"


CKirbyIcon::CKirbyIcon()
{
}

CKirbyIcon::~CKirbyIcon()
{
}

void CKirbyIcon::OnMouseEnter()
{
}

void CKirbyIcon::OnMouseOver()
{
}

void CKirbyIcon::OnMouseExit()
{
}

void CKirbyIcon::OnMouseUp()
{
}

void CKirbyIcon::OnMouseDown()
{
}

void CKirbyIcon::OnMouseClicked()
{
}

void CKirbyIcon::Init()
{
	StatusImage				= RESOURCE->LoadImg(L"PlayerStatus", L"Image\\Kirby\\Basic\\Nomal.png");

	StatusImageIce			= RESOURCE->LoadImg(L"PlayerStatusIce", L"Image\\Kirby\\Ice\\Ice.png");
	StatusImageIceMark		= RESOURCE->LoadImg(L"PlayerStatusIceMark", L"Image\\Kirby\\Ice\\IceItem.png");

	StatusImageSword		= RESOURCE->LoadImg(L"PlayerStatusSwordIcon1", L"Image\\Kirby\\SwordKirby\\Sword Icons1.png");
	StatusImageSwordMark	= RESOURCE->LoadImg(L"PlayerStatusSwordIcon", L"Image\\Kirby\\SwordKirby\\Sword Icons.png");
}

void CKirbyIcon::Update()
{
}

void CKirbyIcon::Render()
{
	if (GAME->swordicon == true)
	{
		RENDER->Image(StatusImageSword, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 100, m_vecRenderPos.y + 35);
		RENDER->Image(StatusImageSwordMark, m_vecRenderPos.x + 25, m_vecRenderPos.y - 50, m_vecRenderPos.x + 75, m_vecRenderPos.y);
	}
	else if (GAME->iceicon == true)
	{
		RENDER->Image(StatusImageIce, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 100, m_vecRenderPos.y + 35);
		RENDER->Image(StatusImageIceMark, m_vecRenderPos.x + 25, m_vecRenderPos.y - 50, m_vecRenderPos.x + 75, m_vecRenderPos.y);
	}
	else
		RENDER->Image(StatusImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 100, m_vecRenderPos.y + 35);
}

void CKirbyIcon::Release()
{
}
