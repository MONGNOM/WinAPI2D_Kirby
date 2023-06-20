#include "framework.h"
#include "CGameManager.h"
#include "CKirby.h"

CGameManager::CGameManager()
{
	ice = false;
	sword = false;
	iceicon = false;
	swordicon = false;


	BossHp = 11;
	maxHp = 5;
	curHp = maxHp;
	playerPos = Vector(0, 0);
}

CGameManager::~CGameManager()
{
}

void CGameManager::Init()
{
}

void CGameManager::Update()
{
}

void CGameManager::Render()
{
}

void CGameManager::GetPlayerHp()
{
	GAME->curHp;
}
