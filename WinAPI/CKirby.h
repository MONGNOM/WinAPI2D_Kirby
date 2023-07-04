#pragma once
#include "CGameObject.h"
#include "CKirbyHp.h"
#include "CEffect.h"



class CKirby : public CGameObject
{
public:
	CKirby();
	virtual ~CKirby();

	const float TIME_DASHABLE = 0.5f;
	const float TIME_FALLING = 0.5f;
	bool m_groundchecker;

public:
	float playerHp;
	float fallTimer;
	float flyTimer;
	CEffect* effect;


	float m_fSpeed;
	float m_jumpSpeed;
	float m_gravity;
	int m_groundCounter;
	bool stage1;

	CSound* JumpSound;
	CSound* RunSound;

	CSound* DamageSound;
	CSound* FlySound;
	CSound* TeleportSound;

	void Effect(float x);

	void SelectSound(CSound* pSound, float volume, bool loop);


	CKirbyHp* hp;

	Vector m_vecMoveDir;
	Vector m_vecLookDir;

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	virtual void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

	float lastLeftInputTime;
	float lastRightInputTime;
};

