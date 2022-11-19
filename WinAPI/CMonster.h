#pragma once
#include "CGameObject.h"

class CPlayer;

class CMonster : public CGameObject
{
	friend CPlayer;
public:
	CMonster();
	virtual ~CMonster();

	void SetDir(Vector dir);
	void SetVelocity(float velocity);

private:

	bool m_Gravity = true;
	Vector m_vecDir;
	float m_fVelocity;
	float m_fSpeed = 200.0f;
<<<<<<< HEAD
<<<<<<< HEAD
	CImage* m_mMoveImage;
	CImage* m_mDieImage;
	CAnimator* m_pAnimator;
	bool slide;
	float slideTime;
	int m_mHp;
=======

>>>>>>> parent of 812e713 (feat : 보스 몬스터 및 플레이어 변신 및 상호작용 문 구현)
=======

>>>>>>> parent of 812e713 (feat : 보스 몬스터 및 플레이어 변신 및 상호작용 문 구현)
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void Gravity();

protected:
	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};

