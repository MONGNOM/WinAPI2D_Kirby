#pragma once
#include "CGameObject.h"

class CPlayer;

class CKIngMonster : public CGameObject
{
	friend CPlayer;
public:
	CKIngMonster();
	virtual ~CKIngMonster();

	void SetDir(Vector dir);
	void SetVelocity(float velocity);

private:
	float MoveTime;
	bool Moveing;

	bool m_Gravity = true;
	Vector m_vecDir;
	float m_fVelocity;
	float JumpTime;
	float m_fSpeed = 200.0f;
	CImage* m_mMoveImage;
	CImage* m_mMoveImageR;
	CImage* m_mDieImage;
	CImage* m_mJumpImage;
	CImage* m_mAttackImage;
	CAnimator* m_pAnimator;
	wstring str = L"";

	int m_mHp;
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void Gravity();

	bool Jump2;
	Vector m_vecMoveDir;
	Vector m_vecLookDir;
	bool m_bIsMove;
	bool Iscrash;
	float DieTime;

	int ontile;

	void Jump();
	void Move();

	void AnimatorUpdate();

protected:
	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};

