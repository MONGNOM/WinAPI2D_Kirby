#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

enum class state {Idle, Walk, Run, Jump, Sit, Fly, Attack};
class CKirby : public CGameObject
{

public:
	CKirby();
	virtual ~CKirby();

private:
	CAnimator* m_pAnimator;

	float runTimer;
	Vector m_vecMoveDir;
	Vector m_vecLookDir;
	wstring kirbystate;
	state m_state;
	float m_fSpeed;

	void IdleState();

	CImage* m_pIdleLImage;
	CImage* m_pIdleRImage;
	CImage* m_pMoveLImage;
	CImage* m_pMoveRImage;
	CImage* m_pRunImage;

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
};

