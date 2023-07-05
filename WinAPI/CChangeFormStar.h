#pragma once
#include "CGameObject.h"

class Image;
class Animator;

class CChangeFormStar : public CGameObject
{
public:
	CChangeFormStar();
	virtual ~CChangeFormStar();

	CAnimator* m_pAnimator;
	CImage* m_pChangeFormStarImage;


private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void OnCollisionStay(CCollider* pOtherCollider) override;

};

