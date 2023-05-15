#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

class CKirby : public CGameObject
{
public:
	CKirby();
	virtual ~CKirby();

	enum class State { Idle, Walk, Run, Jump, Sit, Fly, Attack };

	const float TIME_DASHABLE = 0.5;

private:
	CAnimator* m_pAnimator;

	float runTimer;
	Vector m_vecMoveDir;
	Vector m_vecLookDir;
	wstring kirbystate;
	State m_state;
	float m_fSpeed;
	float m_jumpSpeed;

	void IdleState();
	void WalkState();
	void RunState();
	void JumpState();
	void SitState();
	void FlyState();
	virtual void AttackState();

	CImage* m_pIdleLImage;
	CImage* m_pIdleRImage;
	CImage* m_pMoveLImage;
	CImage* m_pMoveRImage;
	CImage* m_pRunImage;
	CImage* m_pDownImage;
	CImage* m_pFlyImage;
	CImage* m_pFlyingImage;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();
	void CreateMissile();

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

	float lastLeftInputTime;
	float lastRightInputTime;
};

