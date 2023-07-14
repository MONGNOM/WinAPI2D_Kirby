#pragma once
#include "CKirby.h"
#include "CKirbyEat.h"

class CImage;
class CAnimator;
class CKirbyShot;
class CIceKirby;
class CSwordKirby;

class CNomalKirby : public CKirby
{
public:

	enum class State { Idle, Walk, Run, Jump, Sit, Fly, Attack, Flying, JumpingDown, Eating, Change, EatWalk, EatAttack, Disappear, Damage, Invincivle};

	CNomalKirby();
	virtual ~CNomalKirby();

	bool sword;
	bool ice;
	bool eat;
	bool eating;
	bool iceicon;
	bool swordicon;
	void DisappearState();
	void DamageState();
	State m_state;

private:
	CSound* ChangeSound;
	CSound* NotChangeSound;
	CSound* EattingSound;
	CSound* EatSound;
	CSound* ShotSound;

	wstring normalkirbystate;
	CAnimator* m_pAnimator;

	float damageTimer;
	float invincivleTimer;
	float attackTimer;
	float changeTimer;
	float shotTimer;
	void Jump();
	void InvincivleState();
	void IdleState();
	void WalkState();
	void RunState();
	void JumpState();
	void SitState();
	void FlyState();
	void JumpingDownState();
	void FlyingState();
	void AttackState();
	void EatingState();
	void ChangeState();
	void EatWalkState();
	void EatAttackState();
	void AttackCollider();
	void IceKirbyChange();
	void SwordirbyChange();

	CIceKirby* icekirby;
	CSwordKirby* swordKriby;

	CImage* m_pIdleLImage;
	CImage* m_pIdleRImage;
	CImage* m_pMoveLImage;
	CImage* m_pMoveRImage;
	CImage* m_pRunImage;
	CImage* m_pDownImage;
	CImage* m_pFlyImage;
	CImage* m_pJumpImage;
	CImage* m_pJumpingImage;
	CImage* m_pAttackImage;
	CImage* m_pEatChangeImage;
	CImage* m_pEatWalkImage;
	CImage* m_pEatAttackImage;

	CImage* m_pDamageLImage;
	CImage* m_pDamageRImage;
	CImage* m_pInvincivleRImage;
	CImage* m_pInvincivleLImage;

	CKirbyEat* m_pKirbyEat;
	CKirbyShot* m_pKirbyShot;


private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();

	void OnCollisionEnter(CCollider* pOtherCollider) override;



};

