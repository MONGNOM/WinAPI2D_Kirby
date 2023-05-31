#pragma once
#include "CKirbyWeapon.h"

class Image;
class Animator;

class CKirbyShot : public CKirbyWeapon
{
public:
	CKirbyShot(Vector dir);
	virtual ~CKirbyShot();
	
	CAnimator* m_pAnimator;
	CImage* m_pAttackImage;

public:
	void Init() override;
	void Update() override;
	void OnCollisionEnter(CCollider* pOtherCollider);
};

