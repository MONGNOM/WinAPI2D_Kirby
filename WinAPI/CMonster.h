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

	Vector m_vecDir;
	float m_fVelocity;

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;



	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};

