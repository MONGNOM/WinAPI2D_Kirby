#pragma once
#include "WinApi.h"
#include "CKirby.h"

class CGameManager : public SingleTon<CGameManager>
{
	friend SingleTon<CCameraManager>;
	friend CCore;
	friend CKirby;
	enum class PlayerState {Normal, Ice, Sword};

public:
	CGameManager();
	virtual ~CGameManager();
	//PlayerState state;
	float playerHp;
	CKirby* kirby;
public:
	//void Init();		// 게임시작시 초기화 작업
	//void Update();		// 프레임마다 게임로직 진행
	//void Render();		// 프레임마다 게임표현 진행\

	void GetPlayerHp();
};

#define	GAME	CGameManager::GetInstance()
