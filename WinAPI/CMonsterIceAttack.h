#pragma once
#include "CMonsterWeapon.h"
class Image;
class Animator;

class CMonsterIceAttack : public CMonsterWeapon
{
public:
	CMonsterIceAttack();
	virtual ~CMonsterIceAttack();

	CAnimator* m_pAnimator;
	CImage* m_pAttackImage;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

