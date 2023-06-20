#pragma once
#include "WinApi.h"
#include "CKirby.h"

class CGameManager : public SingleTon<CGameManager>
{
	friend SingleTon<CCameraManager>;
	friend CCore;

public:
	CGameManager();
	virtual ~CGameManager();


	bool ice;
	bool sword;
	bool iceicon;
	bool swordicon;

	int BossHp;
	float maxHp;
	float curHp;

	Vector playerPos;
public:
	void Init();		// 게임시작시 초기화 작업
	void Update();		// 프레임마다 게임로직 진행
	void Render();		// 프레임마다 게임표현 진행\

	void GetPlayerHp();
};

#define	GAME	CGameManager::GetInstance()
