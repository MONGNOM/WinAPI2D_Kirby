#pragma once
#include "CGameObject.h"
class CMonsterWeapon : public CGameObject
{
public:
	CMonsterWeapon();
	virtual ~CMonsterWeapon();
	Vector m_vecLookDir;


protected:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

