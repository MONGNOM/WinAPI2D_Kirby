#pragma once
#include "CKirbyWeapon.h"
#include "CEffect.h"

class Image;
class Animator;

class CKirbyShot : public CKirbyWeapon
{
public:
	CKirbyShot(Vector dir);
	virtual ~CKirbyShot();
	

	CAnimator* m_pAnimator;
	CImage* m_pAttackImage;
	CEffect* effect;

public:
	void Init() override;
	void Update() override;
	void OnCollisionEnter(CCollider* pOtherCollider);
};

