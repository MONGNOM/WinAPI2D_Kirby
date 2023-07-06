#include "framework.h"
#include "CTransFormPanel.h"

CTransFormPanel::CTransFormPanel()
{
	m_picemainImage = nullptr;
	m_pswordmainImage = nullptr;
	m_vecPos = Vector(0, 0);
	ClickSound = RESOURCE->LoadSound(L"ClickSound", L"Sound\\Click.wav");

}

CTransFormPanel::~CTransFormPanel()
{
}

void CTransFormPanel::PickPanel(wstring key)
{
	m_vecPos = Vector(CAMERA->GetLookAt().x, CAMERA->GetLookAt().y);
	
}

void CTransFormPanel::OnMouseEnter()
{
}

void CTransFormPanel::OnMouseOver()
{
}

void CTransFormPanel::OnMouseExit()
{
}

void CTransFormPanel::OnMouseUp()
{
}

void CTransFormPanel::OnMouseDown()
{
}

void CTransFormPanel::OnMouseClicked()
{
}

void CTransFormPanel::Init()
{
	m_pswordmainImage = RESOURCE->LoadImg(L"icemain", L"Image\\Kirby\\SwordKirby\\sword kirby main.png");
	m_picemainImage = RESOURCE->LoadImg(L"swordmain", L"Image\\Kirby\\Ice\\IcePanel.png");
}

void CTransFormPanel::Update()
{
	m_vecPos = Vector(CAMERA->GetLookAt().x, CAMERA->GetLookAt().y);

	if (BUTTONDOWN('B'))
	{
		SOUND->Play(ClickSound, 0.1f, false);
		DELETEOBJECT(this);
	}
}

void CTransFormPanel::Render()
{
	
	RENDER->Image(m_picemainImage, m_vecRenderPos.x -420, m_vecRenderPos.y -300, m_vecRenderPos.x + 400, m_vecRenderPos.y + 300);
	/*RENDER->Image(m_pswordmainImage, 0, 0, m_vecPos.x - WINSIZEX * 0.5, m_vecPos.y + WINSIZEY * 0.5);*/
}

void CTransFormPanel::Release()
{
}
