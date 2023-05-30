#pragma once
#include "CKirbyWeapon.h"
class Image;
class Animator;

class CIceAttack : public CKirbyWeapon
{
public:
	CIceAttack();
	virtual ~CIceAttack();

	CAnimator* m_pAnimator;
	CImage* m_pAttackImage;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

