#pragma once
#include "CGameObject.h"
#include "CPlayer.h"

class CImage;
class CAnimator;
class CMonster;
class KirbyEat;

class CLightKirby : public CPlayer
{
	friend KirbyEat;
	friend CPlayer;
	friend CMonster;
public:
	CLightKirby();
	virtual ~CLightKirby();

private:

	bool m_Basic;
	bool m_LightChange;
	bool m_Gravity;
	CAnimator* m_pAnimator;

	CImage* m_pIdleImageR;
	CImage* m_pIdleImageD;
	CImage* m_pIdleImageU;
	CImage* m_pIdleImageL;
	CImage* m_pMoveImage;
	CImage* m_pAttackImage;
	CImage* m_pChangeImage;


	Vector m_vecMoveDir;
	Vector m_vecLookDir;
	bool m_bIsMove;
	float m_fSpeed = 200.0f;

	int ontile;
protected:
	bool m_Eat;


	float JumpTime;
	bool Jumpgo;
	float LastJumpTime;
	float LastRunTime;
	float GravityJumpTime;


private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;


	void LightChange();
	void Gravity();
	void Eat();
	void AnimatorUpdate();
	void Shot();

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};

