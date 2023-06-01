#pragma once
#include "CMonster.h"

class Image;
class Animator;

class CBossMonster : public CMonster
{
	enum class State { Idle, Walk, Attack, Attack2, Die, Dizzy, Jump};

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
	void AttackState2();
	void DieState();
	void DizzyState();
	void JumpState();
	
	CImage* m_pIdleImage;
	CImage* m_pMoveImage;
	CImage* m_pDieImage;
	CImage* m_pAttackImage;
	CImage* m_pAttackImage2;
	CImage* m_pIceDieImage;
	CImage* m_pJumpImage;

	CImage* m_pAttackImageL2;


	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();
};

