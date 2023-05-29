#pragma once
#include "CGameObject.h"
class CMonster;
class CKirbyWeapon : public CGameObject
{
public:
	CKirbyWeapon();
	virtual ~CKirbyWeapon();
	int damage;

protected:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

