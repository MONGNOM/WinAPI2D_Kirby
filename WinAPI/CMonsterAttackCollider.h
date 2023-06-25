#pragma once
#include "CGameObject.h"
#include "CIceMonster.h"
#include "CSwordMonster.h"

class CIceMonster;
class CSwordMonster;
class CMonsterAttackCollider : public CGameObject
{
public:
	CMonsterAttackCollider();
	virtual ~CMonsterAttackCollider();

public:
	float colliderx;
	float collidery;
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	CIceMonster* icemonster;
	CSwordMonster* swordmonster;


	void SetColliderScale(float x, float y);
	void SetIceMonster(CIceMonster* ice);
	void SetSwordMonster(CSwordMonster* sword);

	void OnCollisionEnter(CCollider* pOtherCollider);
};

