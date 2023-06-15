#pragma once
#include "CItem.h"

class CImage;

class CPersimmon : public CItem
{
public:
	CPersimmon();
	virtual ~CPersimmon();

	CImage* image;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void OnCollisionEnter(CCollider* pOtherCollider) override;
};

