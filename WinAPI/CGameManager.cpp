#include "framework.h"
#include "CGameManager.h"
#include "CKirby.h"

CGameManager::CGameManager()
{
	ice = false;
	sword = false;
	maxHp = 5;
	curHp = maxHp;
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
