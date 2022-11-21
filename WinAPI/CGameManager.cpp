#include "framework.h"
#include "CGameManager.h"
#include "CKirbyHp.h"

CGameManager::CGameManager()
{
	PlayerPos = Vector(0, 0);
	PlayerHp = 5;
	BossHp = 11;
	changePlayerLight = false;
	changePlayerIce = false;

	Changeice = false;
	ChangeBasci = false;
	ChangeLight = false;
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

void CGameManager::Enter()
{
}


void CGameManager::Release()
{
}

void CGameManager::GetPlayerHp()
{
	GAME->PlayerHp;
}
