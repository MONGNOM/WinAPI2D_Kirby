#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;
class CMonster;
class KirbyEat;


enum class Playerstate { Idle, Run, Jump, Eat, Shot, Change, Takehit };


class CPlayer : public CGameObject
{
	friend KirbyEat;
	friend CMonster;
public:
	CPlayer();
	virtual ~CPlayer();

private:

	bool m_Basic;
	bool m_LightChange;
	bool m_Gravity;
	CAnimator* m_pAnimator;
	
	CImage* m_pIdleImage;
	CImage* m_pMoveImage;

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

