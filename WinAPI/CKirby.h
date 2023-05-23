#pragma once
#include "CGameObject.h"

class CKirby : public CGameObject
{
public:
	CKirby();
	virtual ~CKirby();

	const float TIME_DASHABLE = 0.5f;
	const float TIME_FALLING = 0.5f;
	bool m_groundchecker;

public:
	float fallTimer;
	float flyTimer;

	float m_fSpeed;
	float m_jumpSpeed;
	float m_gravity;
	int m_groundCounter;

	Vector m_vecMoveDir;
	Vector m_vecLookDir;

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

	float lastLeftInputTime;
	float lastRightInputTime;
};

