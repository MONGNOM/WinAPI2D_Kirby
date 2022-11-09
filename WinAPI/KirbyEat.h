#pragma once
#include "CGameObject.h"

class CPlayer;

class KirbyEat : public CGameObject
{

	friend CPlayer;
public:
	KirbyEat();
	virtual~KirbyEat();

private:

	Vector m_vecDir;


	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

public:
	void SetDir(Vector dir);

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};

