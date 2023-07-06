#pragma once
#include "CGameObject.h"

class Image;
class Animator;
class CNomalKirby;

class CChangeFormStar : public CGameObject
{
public:
	CChangeFormStar();
	virtual ~CChangeFormStar();

	CAnimator* m_pAnimator;
	CImage* m_pChangeFormStarImage;
	CSound* DeathSound;
	wstring changeFormStar;
	void ChangeStarName(wstring Name);

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void AnimatorUpdate();

	void OnCollisionEnter(CCollider* pOtherCollider);

};

