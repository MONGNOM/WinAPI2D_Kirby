#pragma once
#include "CItem.h"

class Image;
class Animator;

class CSwordItem : public CItem
{
public:
	CSwordItem();
	virtual ~CSwordItem();

	CAnimator* m_pAnimator;
	CImage* m_pSwordItemImage;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

