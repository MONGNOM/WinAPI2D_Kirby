#include "framework.h"
#include "CGameManager.h"
#include "CKirby.h"

CGameManager::CGameManager()
{
	ice = false;
	sword = false;

	iceicon = false;
	swordicon = false;
	
	PlayerHit = false;
	HpNotDown = false;
	HitTime = 0;

	monsterHit = false;
	monsterhpnotDown = false;
	monsterhitTime = 0;

	BossHp = 11;
	maxHp = 5;
	curHp = maxHp;
	playerPos = Vector(0, 0);
	invincible = 0;
	playerLoockDirX = 0;
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
		if (HitTime >= 2.f)
		{
			HpNotDown = false;
			HitTime = 0;
			PlayerHit = false;
		}
	}

	if (monsterHit == true)
	{
		monsterhpnotDown = true;
		monsterhitTime += DT;
		if (monsterhitTime >= invincible)
		{
			monsterhpnotDown = false;
			monsterhitTime = 0;
			monsterHit = false;
		}
	}
}

void CGameManager::Render()
{
}

void CGameManager::GetPlayerHp()
{
	GAME->curHp;
}
