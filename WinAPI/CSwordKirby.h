#pragma once
#include "CKirby.h"
class CSwordKirby : public CKirby
{
	enum class State { Idle, Walk, Run, Jump, Sit, Fly, Attack, Flying, JumpingDown, Attacking };

	CSwordKirby();
	virtual ~CSwordKirby();

	float attackTimer;


private:

	wstring swordkirbystate;
	State m_state;
	CAnimator* m_pAnimator;

	void Jump();
	void IdleState();
	void WalkState();
	void RunState();
	void JumpState();
	void SitState();
	void FlyState();
	void JumpingDownState();
	void FlyingState();
	void AttackState();
	void AttackingState();

	CImage* m_pIdleImage;
	CImage* m_pMoveImage;
	CImage* m_pRunImage;
	CImage* m_pDownImage;
	CImage* m_pFlyImage;
	CImage* m_pJumpImage;
	CImage* m_pAttackImage;


private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();
};

