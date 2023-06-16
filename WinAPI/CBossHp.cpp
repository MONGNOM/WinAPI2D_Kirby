#include "framework.h"
#include "CBossHp.h"
#include "CGameManager.h"

CBossHp::CBossHp()
{
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
	HpImage = RESOURCE->LoadImg(L"BossHP", L"Image\\Monster\\King\\KingHp.png");

}

void CBossHp::Update()
{
}

void CBossHp::Render()
{
	if (GAME->BossHp == 11)
		RENDER->Image(HpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 200, m_vecRenderPos.y + 64);
	else if (GAME->BossHp == 10)
	{
		RENDER->Image(HpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 200, m_vecRenderPos.y + 64);
		RENDER->FillRect(m_vecRenderPos.x + 180, m_vecRenderPos.y + 27.8f, m_vecRenderPos.x + 149.2f, m_vecRenderPos.y + 49.2f);
	}
	else if (GAME->BossHp == 9)
	{
		RENDER->Image(HpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 200, m_vecRenderPos.y + 64);
		RENDER->FillRect(m_vecRenderPos.x + 180, m_vecRenderPos.y + 27.8f, m_vecRenderPos.x + 134.2f, m_vecRenderPos.y + 49.2f);
	}
	else if (GAME->BossHp == 8)
	{
		RENDER->Image(HpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 200, m_vecRenderPos.y + 64);
		RENDER->FillRect(m_vecRenderPos.x + 180, m_vecRenderPos.y + 27.8f, m_vecRenderPos.x + 119.2f, m_vecRenderPos.y + 49.2f);
	}
	else if (GAME->BossHp == 7)
	{
		RENDER->Image(HpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 200, m_vecRenderPos.y + 64);
		RENDER->FillRect(m_vecRenderPos.x + 180, m_vecRenderPos.y + 27.8f, m_vecRenderPos.x + 104.2f, m_vecRenderPos.y + 49.2f);
	}
	else if (GAME->BossHp == 6)
	{
		RENDER->Image(HpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 200, m_vecRenderPos.y + 64);
		RENDER->FillRect(m_vecRenderPos.x + 180, m_vecRenderPos.y + 27.8f, m_vecRenderPos.x + 99.2f, m_vecRenderPos.y + 49.2f);
	}
	else if (GAME->BossHp == 5)
	{
		RENDER->Image(HpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 200, m_vecRenderPos.y + 64);
		RENDER->FillRect(m_vecRenderPos.x + 180, m_vecRenderPos.y + 27.8f, m_vecRenderPos.x + 84.2f, m_vecRenderPos.y + 49.2f);

	}
	else if (GAME->BossHp == 4)
	{
		RENDER->Image(HpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 200, m_vecRenderPos.y + 64);
		RENDER->FillRect(m_vecRenderPos.x + 180, m_vecRenderPos.y + 27.8f, m_vecRenderPos.x + 69.2f, m_vecRenderPos.y + 49.2f);
	}
	else if (GAME->BossHp == 3)
	{
		RENDER->Image(HpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 200, m_vecRenderPos.y + 64);
		RENDER->FillRect(m_vecRenderPos.x + 180, m_vecRenderPos.y + 27.8f, m_vecRenderPos.x + 54.2f, m_vecRenderPos.y + 49.2f);
	}
	else if (GAME->BossHp == 2)
	{
		RENDER->Image(HpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 200, m_vecRenderPos.y + 64);
		RENDER->FillRect(m_vecRenderPos.x + 180, m_vecRenderPos.y + 27.8f, m_vecRenderPos.x + 49.2f, m_vecRenderPos.y + 49.2f);
	}
	else if (GAME->BossHp == 1)
	{
		RENDER->Image(HpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 200, m_vecRenderPos.y + 64);
		RENDER->FillRect(m_vecRenderPos.x + 180, m_vecRenderPos.y + 27.8f, m_vecRenderPos.x + 34.2f, m_vecRenderPos.y + 49.2f);
	}
	else if (GAME->BossHp == 0)
	{
		RENDER->Image(HpImage, m_vecRenderPos.x, m_vecRenderPos.y, m_vecRenderPos.x + 200, m_vecRenderPos.y + 64);
		RENDER->FillRect(m_vecRenderPos.x + 180, m_vecRenderPos.y + 27.8f, m_vecRenderPos.x + 19.2f, m_vecRenderPos.y + 49.2f);
	}
}

void CBossHp::Release()
{
}
