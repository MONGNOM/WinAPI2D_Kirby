#pragma once
#include "CMonster.h"

class CImage;
class CAnimator;

class CBasicMonster : public CMonster
{
public:

	enum class State { Walk, Die, Dizzy, Disappear};

	CBasicMonster();
	virtual ~CBasicMonster();

private:

	wstring Basicstate;
	State m_state;
	CAnimator* m_pAnimator;
	

	void WalkState();
	void DieState();
	void DizzyState();
	void DisappearState();

	CImage* m_pIceDieImage;

	CImage* m_pMoveImage;
	CImage* m_pDieImage;


private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();
};

