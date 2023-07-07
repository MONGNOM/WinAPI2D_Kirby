#include "framework.h"
#include "CTransFormPanel.h"
#include "CGameManager.h"
CTransFormPanel::CTransFormPanel()
{
	m_picemainImage = nullptr;
	m_pswordmainImage = nullptr;
	m_vecPos = Vector(0, 0);
	ClickSound = RESOURCE->LoadSound(L"ClickSound", L"Sound\\Click.wav");
	m_layer = Layer::Panel;
	panelTimer = 0;

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
	
	CAMERA->FadeOut(0.0001f);
	m_pswordmainImage = RESOURCE->LoadImg(L"icemain", L"Image\\Kirby\\SwordKirby\\sword kirby main.png");
	m_picemainImage = RESOURCE->LoadImg(L"swordmain", L"Image\\Kirby\\Ice\\IcePanel.png");


}

void CTransFormPanel::Update()
{
	panelTimer += DT;
	if (panelTimer > 0.5f)
	{
		CAMERA->FadeIn(0.1f, 1.0f);
	}
	m_vecPos = Vector(400,300);

	if (BUTTONDOWN('B'))
	{
		SOUND->Play(ClickSound, 0.1f, false);
		DELETEOBJECT(this);
	}
}

void CTransFormPanel::Render()
{
	
	RENDER->Image(m_picemainImage, m_vecRenderPos.x -420, m_vecRenderPos.y -300, m_vecRenderPos.x + 400, m_vecRenderPos.y + 300);
	/*RENDER->Image(m_pswordmainImage, 0, 0, m_vecPos.x - WINSIZEX * 0.5f, m_vecPos.y + WINSIZEY * 0.5f);*/
}

void CTransFormPanel::Release()
{
}
