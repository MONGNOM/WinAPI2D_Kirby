#pragma once
#include "CItem.h"

class CImage;

class CMeat : public CItem
{

public:
	CMeat();
	virtual ~CMeat();

	CImage* image;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void OnCollisionEnter(CCollider* pOtherCollider) override;

};

