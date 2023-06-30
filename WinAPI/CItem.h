#pragma once
#include "CGameObject.h"
class CItem : public CGameObject
{
public:
	CItem();
	virtual ~CItem();

	CSound* ItemGetSound;
	CSound* HealHpSound;

protected:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	virtual void OnCollisionEnter(CCollider* pOtherCollider) override;

};

