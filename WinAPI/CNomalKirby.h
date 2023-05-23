#pragma once
#include "CKirby.h"

class CImage;
class CAnimator;

class CNomalKirby : public CKirby
{
public:
	CNomalKirby();
	~CNomalKirby();

private:
	CAnimator* m_pAnimator;

	CImage* m_pIdleLImage;
	CImage* m_pIdleRImage;
	CImage* m_pMoveLImage;
	CImage* m_pMoveRImage;
	CImage* m_pRunImage;
	CImage* m_pDownImage;
	CImage* m_pFlyImage;
	CImage* m_pFlyingImage;
	CImage* m_pJumpImage;
	CImage* m_pJumpingImage;
	CImage* m_pAttackImage;

	wstring kirbystate;

private:

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void Attack() override;
	void AnimatorUpdate() override;
};

