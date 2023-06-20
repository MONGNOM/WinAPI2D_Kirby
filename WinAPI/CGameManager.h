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
	void Init();		// ���ӽ��۽� �ʱ�ȭ �۾�
	void Update();		// �����Ӹ��� ���ӷ��� ����
	void Render();		// �����Ӹ��� ����ǥ�� ����\

	void GetPlayerHp();
};

#define	GAME	CGameManager::GetInstance()
