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
	//void Init();		// ���ӽ��۽� �ʱ�ȭ �۾�
	//void Update();		// �����Ӹ��� ���ӷ��� ����
	//void Render();		// �����Ӹ��� ����ǥ�� ����\

	void GetPlayerHp();
};

#define	GAME	CGameManager::GetInstance()
