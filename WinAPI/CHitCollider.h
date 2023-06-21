#pragma once
#include "CGameObject.h"
class CMonster;
class CHitCollider : public CGameObject
{
public:
	CHitCollider();
	virtual ~CHitCollider();

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CMonster* monster;

	void SetMonster(CMonster* monster);

	void OnCollisionEnter(CCollider* pOtherCollider);

};

