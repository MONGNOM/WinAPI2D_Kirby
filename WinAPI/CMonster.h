#pragma once
#include "CGameObject.h"

class CMonster : public CGameObject
{
public:
	CMonster();
	virtual ~CMonster();

	float dieTime;
	int hp;
	bool dizzy;
	bool m_groundchecker;
	
	Vector m_vecLookDir; 
	Vector m_vecMoveDir;
	
	int m_groundCounter;
	float m_fSpeed;
	float m_gravity;
public:
	void TakeDamage(int damage);


protected:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};

