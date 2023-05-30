#pragma once
#include "CKirbyWeapon.h"
class CSword : public CKirbyWeapon
{
public:
	CSword();
	virtual ~CSword();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void SetColliderSize(Vector scale, Vector offsetPos);
};

