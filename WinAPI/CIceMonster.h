#pragma once
#include "CMonster.h"
#include "CMonsterIceAttack.h"
#include "CMonsterAttackCollider.h"


class CMonsterAttackCollider;
class CImage;
class CAnimator;

class CIceMonster : public CMonster
{
public: 
	
	enum class State {Walk, Dizzy ,Die, Attack};

	CIceMonster();
	virtual ~CIceMonster();

	State m_state;
private:
	wstring iceState;
	CAnimator* m_pAnimator;

	void WalkState();
	void DieState();
	void AttackState();
	void DizzyState();
	CImage* m_pMoveImage;
	CImage* m_pDieImage;
	CImage* m_pIceDieImage;
	CImage* m_pAttackImage;
	CMonsterIceAttack* iceAttack;
	CMonsterAttackCollider* attackCollider;
	void MonsterAttackCollider();

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();
};

