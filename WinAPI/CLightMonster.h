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

protected:
	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};

