#include "framework.h"
#include "CKirbyHp.h"
#include "CGameManager.h"

CKirbyHp::CKirbyHp()
{
	GaugehpImage = nullptr;
	FramehpImage = nullptr;
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
	GaugehpImage = RESOURCE->LoadImg(L"KirbyHP", L"Image\\KirbyHp.png");
	FramehpImage = RESOURCE->LoadImg(L"FrameKirbyHP", L"Image\\KirbyHpFrame.png");
}

void CKirbyHp::Update()
{
}

void CKirbyHp::Render()
{
	RENDER->Image(FramehpImage, m_vecRenderPos.x+10, m_vecRenderPos.y, m_vecRenderPos.x + 195, m_vecRenderPos.y + 50);
	float hpWidth = (m_vecRenderPos.x + 180 - m_vecRenderPos.x) * GAME->curHp / GAME->maxHp;
	RENDER->FrameImage(GaugehpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x  + hpWidth, m_vecRenderPos.y + 50, 0,0,hpWidth,50);

}

void CKirbyHp::Release()
{
}
