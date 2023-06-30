#pragma once
#include "CItem.h"
class Image;
class Animator;

class CIceItem : public CItem
{
public:
	CIceItem();
	virtual ~CIceItem();

	CAnimator* m_pAnimator;
	CImage* m_pIceItemImage;

	
private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

