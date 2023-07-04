#pragma once
#include "CKirbyWeapon.h"
class CKirby;
class Image;
class Animator;

class CIceAttack : public CKirbyWeapon
{
public:
	CIceAttack();
	virtual ~CIceAttack();

	CAnimator* m_pAnimator;
	CImage* m_pAttackImage;
	CKirby* kirby;

	void Attack();
	wstring iceAttackstate;
private:
	void Init() override;
	void Release() override;
	void Render() override;
	void Update() override;
	void AnimatorUpdate();
};



