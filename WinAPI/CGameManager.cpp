#include "framework.h"
#include "CGameManager.h"
#include "CKirby.h"

CGameManager::CGameManager()
{
	playerHp = kirby->hp;
}

CGameManager::~CGameManager()
{
}

//void CGameManager::Init()
//{
//}
//
//void CGameManager::Update()
//{
//}
//
//void CGameManager::Render()
//{
//}

void CGameManager::GetPlayerHp()
{
	GAME->playerHp;
}
