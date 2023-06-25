#pragma once
#include "CGameObject.h"
class CMonster;

class CHitCollider : public CGameObject
{
public:
	CHitCollider();
	virtual ~CHitCollider();

public:
	float colliderx;
	float collidery;
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CMonster* monster;
	

	void SetColliderScale(float x, float y);
	void SetMonster(CMonster* monster);

	void OnCollisionStay(CCollider* pOtherCollider);

};

