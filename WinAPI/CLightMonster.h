#pragma once
#include "CGameObject.h"


class CPlayer;

class CLightMonster : public CGameObject
{
	friend CPlayer;
public:
	CLightMonster();
	virtual ~CLightMonster();

	void SetDir(Vector dir);
	void SetVelocity(float velocity);

private:

	bool m_Gravity = true;
	Vector m_vecDir;
	float m_fVelocity;
	float m_fSpeed = 200.0f;

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void Gravity();
<<<<<<< HEAD
	
	Vector m_vecMoveDir;
	Vector m_vecLookDir;
	bool m_bIsMove;
	bool Iscrash;
	float DieTime;
	bool slide;
	float slideTime;
	void AnimatorUpdate();
=======
>>>>>>> parent of 812e713 (feat : 보스 몬스터 및 플레이어 변신 및 상호작용 문 구현)

protected:
	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};

