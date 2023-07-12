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
	
	bool m_groundchecker;
	int m_groundCounter;



	float m_jumpSpeed;
	float m_gravity;
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
	void AnimatorUpdate();

	void OnCollisionEnter(CCollider* pOtherCollider);
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

};

