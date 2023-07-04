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
	
	enum class State {Walk, Dizzy ,Die, Attack, Disappear};

	CIceMonster();
	virtual ~CIceMonster();

	void DieState();
	State m_state;
private:
	wstring iceState;
	CAnimator* m_pAnimator;
	void DisappearState();
	void WalkState();
	void AttackState();
	void DizzyState();
	CImage* m_pMoveImage;
	CImage* m_pDieImage;
	CImage* m_pIceDieImage;
	CImage* m_pAttackImage;
	CMonsterIceAttack* iceAttack;
	CMonsterAttackCollider* attackCollider;
	void MonsterAttackCollider();
	void OnCollisionEnter(CCollider* pOtherCollider);

	void DeleteObject();

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();
};

