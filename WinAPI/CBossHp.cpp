#include "framework.h"
#include "CBossHp.h"
#include "CGameManager.h"

CBossHp::CBossHp()
{
	m_pBossGaugeHpImage = nullptr;
	m_pBossFrameHpImage = nullptr;
}

CBossHp::~CBossHp()
{
}

void CBossHp::OnMouseEnter()
{
}

void CBossHp::OnMouseOver()
{
}

void CBossHp::OnMouseExit()
{
}

void CBossHp::OnMouseUp()
{
}

void CBossHp::OnMouseDown()
{
}

void CBossHp::OnMouseClicked()
{
}

void CBossHp::Init()
{
	m_pBossGaugeHpImage = RESOURCE->LoadImg(L"BossHPGauge", L"Image\\Monster\\King\\KingHpGauge.png");
	m_pBossFrameHpImage = RESOURCE->LoadImg(L"BossHPFrame", L"Image\\Monster\\King\\KingHpFrame.png");
}

void CBossHp::Update()
{
}

void CBossHp::Render()
{
	RENDER->Image(m_pBossFrameHpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 200, m_vecRenderPos.y + 64);
	float hpWidth = (m_vecRenderPos.x + 200 - m_vecRenderPos.x) *   GAME->Bosscurhp / GAME->BossHp;
	RENDER->FrameImage(m_pBossGaugeHpImage, m_vecRenderPos.x - 23, m_vecRenderPos.y - 15 , m_vecRenderPos.x + hpWidth -22, m_vecRenderPos.y + 49, 0, 0, hpWidth, 64);
	
	
}

void CBossHp::Release()
{
}
