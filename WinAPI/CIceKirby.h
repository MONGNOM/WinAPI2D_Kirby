#pragma once
#include "Ckirby.h"


class CImage;
class CAnimator;

class CIceKirby : public CKirby
{
public:

	enum class State { Idle, Walk, Run, Jump, Sit, Fly, Attack, Flying, JumpingDown, Attacking };

	CIceKirby();
	virtual ~CIceKirby();

	float attackTimer;


private:

	wstring icekirbystate;
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

