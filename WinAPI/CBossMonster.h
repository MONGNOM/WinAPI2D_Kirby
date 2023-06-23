#pragma once
#include "CMonster.h"
#include "CMonsterWeapon.h"


class Image;
class Animator;

class CBossMonster : public CMonster
{
	enum class State { Idle, Walk, Attack, Die, Dizzy, Jump, JumpDown, JumpAttack, Fear, Disappear };

public:
	CBossMonster();
	virtual ~CBossMonster();

private:
	wstring bossstate;
	State m_state;
	CAnimator* m_pAnimator;


	void IdleState();
	void WalkState();
	void AttackState();
	void DieState();
	void DizzyState();
	void JumpState();
	void JumpDownState();
	void JumpAttackState();
	void FearState();
	void DisappearState();
	
	
	void MonsterAttackCollider();

	
	CImage* m_pIdleImage;
	CImage* m_pMoveImage;
	CImage* m_pDieImage;
	CImage* m_pAttackImage;
	CImage* m_pAttackImage2;
	CImage* m_pIceDieImage;
	CImage* m_pJumpImage;
	CImage* m_pAttackImageL2;

	CImage* m_pBossImageR;
	CImage* m_pBossImageL;


	CMonsterWeapon* m_pWeapon;

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();
};

