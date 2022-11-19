#include "framework.h"
#include "CKirbyHp.h"

#include "CPlayer.h"

CKirbyHp::CKirbyHp()
{
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

	HpImage = RESOURCE->LoadImg(L"PlayerHP", L"Image\\KirbyHp.png");
	m_bScreenFixed = true;
}

void CKirbyHp::Update()
{
}

void CKirbyHp::Render()
{
	RENDER->Image(HpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x +180, m_vecRenderPos.y + 50);
}

void CKirbyHp::Release()
{
}
