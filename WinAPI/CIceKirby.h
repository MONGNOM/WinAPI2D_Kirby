#pragma once
#include "Ckirby.h"

class CIceAttack;
class CImage;
class CAnimator;
class CNomalKirby;

class CIceKirby : public CKirby
{
public:

	enum class State { Idle, Walk, Run, Jump, Sit, Fly, Attack, Flying, JumpingDown, Attacking, Takeoff, ChangeForm };

	CIceKirby();
	virtual ~CIceKirby();

	float attackTimer;
	

private:
	State m_state;
	CSound* IceSound;
	CSound* DropSound;

	wstring icekirbystate;
	CAnimator* m_pAnimator;
	CIceAttack* m_piceAttack;
	CNomalKirby* m_pNormalKirby;

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
	void CreatAttackArea();
	void DeleteAttackArea();
	void TakeOffState();
	void ChangeFormState();

	CImage* m_pIdleImage;
	CImage* m_pMoveImage;
	CImage* m_pRunImage;
	CImage* m_pDownImage;
	CImage* m_pFlyImage;
	CImage* m_pJumpImage;
	CImage* m_pAttackImage;
	CImage* m_pChangeFormImage;


private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;


	void OnCollisionEnter(CCollider* pOtherCollider) override;

	void AnimatorUpdate();
};

