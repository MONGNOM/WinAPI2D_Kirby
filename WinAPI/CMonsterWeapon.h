#pragma once
#include "CGameObject.h"
class CMonsterWeapon : public CGameObject
{
public:
	CMonsterWeapon();
	virtual ~CMonsterWeapon();

	float colliderX;
	float colliderY;

	void SetMonsterWeaponScale(float x, float y);
	
protected:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

