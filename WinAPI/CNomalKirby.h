#pragma once
#include "CKirby.h"

class CImage;
class CAnimator;

class CNomalKirby : public CKirby
{
public:

	enum class State { Idle, Walk, Run, Jump, Sit, Fly, Attack, Flying, JumpingDown };

	CNomalKirby();
	virtual ~CNomalKirby();

private:
	
	wstring kirbystate;
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

	CImage* m_pIdleLImage;
	CImage* m_pIdleRImage;
	CImage* m_pMoveLImage;
	CImage* m_pMoveRImage;
	CImage* m_pRunImage;
	CImage* m_pDownImage;
	CImage* m_pFlyImage;
	CImage* m_pFlyingImage;
	CImage* m_pJumpImage;
	CImage* m_pJumpingImage;
	CImage* m_pAttackImage;


private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void Attack();
	void AnimatorUpdate();
	void CreateMissile();

};

