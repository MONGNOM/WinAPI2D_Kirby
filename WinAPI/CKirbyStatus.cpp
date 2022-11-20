#include "framework.h"
#include "CKirbyStatus.h"

CKirbyStatus::CKirbyStatus()
{
}

CKirbyStatus::~CKirbyStatus()
{
}

void CKirbyStatus::SetHp()
{
}

void CKirbyStatus::OnMouseEnter()
{
}

void CKirbyStatus::OnMouseOver()
{
}

void CKirbyStatus::OnMouseExit()
{
}

void CKirbyStatus::OnMouseUp()
{
}

void CKirbyStatus::OnMouseDown()
{
}

void CKirbyStatus::OnMouseClicked()
{
}

void CKirbyStatus::Init()
{
	StatusImage = RESOURCE->LoadImg(L"PlayerStatus", L"Image\\Kirby\\Basic\\Nomal.png");

	StatusImageIce = RESOURCE->LoadImg(L"PlayerStatusIce", L"Image\\Kirby\\Ice\\Ice.png");
	StatusImageIceMark = RESOURCE->LoadImg(L"PlayerStatusIceMark", L"Image\\Kirby\\Ice\\IceItem.png");

	StatusImageLight = RESOURCE->LoadImg(L"PlayerStatusLight", L"Image\\Kirby\\Light\\Beam.png");
	StatusImageLightMark = RESOURCE->LoadImg(L"PlayerStatusLightMark", L"Image\\Kirby\\Light\\BeamITem.png");
	m_bScreenFixed = true;
}

void CKirbyStatus::Update()
{

}

void CKirbyStatus::Render()
{

	if (GAME->changePlayerLight == true)
	{
		RENDER->Image(StatusImageLight, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 100, m_vecRenderPos.y + 35);
		RENDER->Image(StatusImageLightMark, m_vecRenderPos.x , m_vecRenderPos.y - 100, m_vecRenderPos.x + 100, m_vecRenderPos.y );
	}
	else if (GAME->changePlayerIce == true)
	{
		RENDER->Image(StatusImageIce, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 100, m_vecRenderPos.y + 35);
		RENDER->Image(StatusImageIceMark, m_vecRenderPos.x, m_vecRenderPos.y -100, m_vecRenderPos.x + 100, m_vecRenderPos.y);
	}
	else
		RENDER->Image(StatusImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 100, m_vecRenderPos.y + 35);
}

void CKirbyStatus::Release()
{
}
