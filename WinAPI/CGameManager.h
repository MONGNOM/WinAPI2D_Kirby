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

	float maxHp;
	float curHp;
	CKirby* kirby;

	Vector playerPos;
public:
	void Init();		// ���ӽ��۽� �ʱ�ȭ �۾�
	void Update();		// �����Ӹ��� ���ӷ��� ����
	void Render();		// �����Ӹ��� ����ǥ�� ����\

	void GetPlayerHp();
};

#define	GAME	CGameManager::GetInstance()
