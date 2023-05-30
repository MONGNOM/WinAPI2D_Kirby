#pragma once
#include "CKirbyWeapon.h"

class Image;
class CAnimator;

class CKirbyEat : public CKirbyWeapon
{
public:
	CKirbyEat();
	virtual ~CKirbyEat();

	CAnimator* m_pAnimator;
	CImage* m_pAttackImage;

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	//void OnCollisionEnter(CCollider* pOtherCollider) override;

};

