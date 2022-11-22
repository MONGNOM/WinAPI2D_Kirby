#pragma once
#include "WinAPI.h"
class CGameManager : public SingleTon<CGameManager>
{
	friend SingleTon<CGameManager>;
	friend CCore;

public:
	CGameManager();
	virtual ~CGameManager();

private:
	void Init();
	void Update();
	void Enter();
	void Release();
public:
	Vector PlayerPos;
	int PlayerHp;
	int BossHp;

	bool m_DebugMode;
	bool PlayerHit;
	bool HpNotDown;
	float HitTime;

	bool Changeice;
	bool ChangeBasci;
	bool ChangeLight;

	bool changePlayerLight;
	bool changePlayerIce;

	void GetPlayerHp();
};

#define GAME CGameManager::GetInstance()

