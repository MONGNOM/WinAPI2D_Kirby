#pragma once
#include "CGameObject.h"
class CKirbyWeapon : public CGameObject
{
public:
	CKirbyWeapon();
	virtual ~CKirbyWeapon();

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
};

