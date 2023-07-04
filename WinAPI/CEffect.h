#pragma once
#include "CGameObject.h"

class Image;
class Animator;

class CEffect : public CGameObject
{
public:
	CEffect();
	virtual ~CEffect();

	void MonsterDeathEffect();
	void kirbyChangeEffect();
	void NomalAttackDestoryEffect();
	void MonsterIceDeathEffect();
	void KirbyDashEffectL();
	void KirbyDashEffectR();

private:
	wstring Effectstate;
	CAnimator* m_pAnimator;
	CImage* Effect;
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void AnimatorUpdate();
};

