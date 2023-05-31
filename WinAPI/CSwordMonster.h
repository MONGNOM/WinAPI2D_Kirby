#pragma once
#include "CMonster.h"

class CImage;
class CAnimator;

class CSwordMonster :
    public CMonster
{
public:

	enum class State { Idle, Walk, Attack, Attack2, Die, Dizzy};

	CSwordMonster();
	virtual ~CSwordMonster();

private:
	wstring swordstate;
	State m_state;
	CAnimator* m_pAnimator;

	void IdleState();
	void WalkState();
	void AttackState();
	void AttackState2();
	void DieState();
	void DizzyState();

	CImage* m_pIdleImage;
	CImage* m_pMoveImage;
	CImage* m_pDieImage;
	CImage* m_pAttackImage;
	CImage* m_pAttackImage2;
	CImage* m_pIceDieImage;

	CImage* m_pLIdleImage;
	CImage* m_pLAttackImage;
	CImage* m_pLAttackImage2;

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();
};

