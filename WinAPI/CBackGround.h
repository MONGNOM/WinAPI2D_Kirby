#pragma once
#include "CGameObject.h"
class CBackGround : public CGameObject
{
public:

	CBackGround();
	virtual ~CBackGround();

private:
	CAnimator* m_pAnimator;
	CImage* m_pBossmapImage;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

