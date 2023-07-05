#pragma once
#include "CGameObject.h"

class Image;
class Animator;

class CEffect : public CGameObject
{
public:
	CEffect();
	virtual ~CEffect();

	bool effectDestory;
	float effectDestoryTime;

	void MonsterDeathEffect();
	void kirbyChangeEffect();
	void NomalAttackDestoryEffect();
	void MonsterIceDeathEffect();
	void KirbyDashEffectL();
	void KirbyDashEffectR();
	void BossAttackEffect();

private:
	wstring Effectstate;
	CAnimator* m_pAnimator;
	CImage* Effect;
	CImage* BossEffect;
	
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void AnimatorUpdate();
};

