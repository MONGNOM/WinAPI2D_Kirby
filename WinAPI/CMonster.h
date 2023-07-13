#pragma once
#include "CGameObject.h"
#include "CHitCollider.h"
#include "CEffect.h"

class CImage;
class CAnimtor;
class CEffect;

class CMonster : public CGameObject
{
public:
	CMonster();
	virtual ~CMonster();

	float dieTimer;
	float walkTimer;
	float idleTimer;
	float attackTimer;
	

	int hp;
	bool bosseffect;
	bool dizzy;
	bool m_groundchecker;
	CSound* DamageSound;
	CSound* DeathSound;

	CEffect* effect;


	bool iceDie;
	Vector m_vecLookDir; 
	Vector m_vecMoveDir;
	CHitCollider* collider;
	
	int m_groundCounter;
	float m_fSpeed;
	float m_gravity;
public:
	void TakeDamage(int damage);
	void Effect(float x, float y);
	void BossEffect();

protected:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
private:

	float bosseffectTimer;
	CEffect* bossEffect;
	CEffect* bossEffect1;
	CEffect* bossEffect2;
	CEffect* bossEffect3;
	CEffect* bossEffect4;
	CEffect* bossEffect5;
	CEffect* bossEffect6;

public:
	
	CMonster* GetMonster();

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};

