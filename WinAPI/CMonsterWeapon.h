#pragma once
#include "CGameObject.h"
class CMonsterWeapon : public CGameObject
{
public:
	CMonsterWeapon();
	virtual ~CMonsterWeapon();


protected:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

