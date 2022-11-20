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

	bool changePlayerLight;
	bool changePlayerIce;

	void GetPlayerHp();
};

#define GAME CGameManager::GetInstance()

