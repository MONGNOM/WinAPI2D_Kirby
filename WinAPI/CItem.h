#pragma once
#include "CGameObject.h"
class CItem : public CGameObject
{
public:
	CItem();
	virtual ~CItem();


protected:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void OnCollisionEnter(CCollider* pOtherCollider) override;

};

