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

	PlayerHit = false;
	HitTime = 0;
	Changeice = false;
	ChangeBasci = false;
	HpNotDown = false;
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
	if (PlayerHit == true)
	{
		HpNotDown = true;
		HitTime += DT;
		if (HitTime >= 2)
		{
			HpNotDown = false;
			HitTime = 0;
			PlayerHit = false;
		}
	}
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
