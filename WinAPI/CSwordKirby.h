#pragma once
#include "CKirby.h"
class CSword;
class CSwordKirby : public CKirby
{
	enum class State { Idle, Walk, Run, Jump, Sit, Fly, Attack, Flying, JumpingDown, JumpAttack, DownAttack, Attacking, DownJumpAttack};

public:
	CSwordKirby();
	virtual ~CSwordKirby();

	float attackTimer;


private:

	wstring swordkirbystate;
	State m_state;
	CAnimator* m_pAnimator;
	CSword* m_pSword;
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
	void JumpAttackState();
	void DownAttackState();
	void DownJumpAttackState();
	void AttackingState();
	void AttackCollider();
	void AttackCollider(Vector position, Vector scale);



	CImage* m_pIdleImage;
	CImage* m_pMoveImage;
	CImage* m_pRunImage;
	CImage* m_pDownImage;
	CImage* m_pFlyImage;
	CImage* m_pJumpImage;
	CImage* m_pAttackImage;
	CImage* m_pDownAttackImage;
	CImage* m_pJumpingImage;
	CImage* m_pFlyingImage;
	CImage* m_pJumpAttackImage;
	CImage* m_pJumpDownImage;
	CImage* m_pDownJumpAttackImage;
	CImage* m_pAttackingImage;

	CImage* m_LpIdleImage;
	CImage* m_LpMoveImage;
	CImage* m_LpRunImage;
	CImage* m_LpDownImage;
	CImage* m_LpFlyImage;
	CImage* m_LpJumpImage;
	CImage* m_LpAttackImage;
	CImage* m_LpDownAttackImage;
	CImage* m_LpJumpingImage;
	CImage* m_LpFlyingImage;
	CImage* m_LpJumpAttackImage;
	CImage* m_LpJumpDownImage;
	CImage* m_LpDownJumpAttackImage;
	CImage* m_LpAttackingImage;



private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();
};

