#pragma once
#include "CGameObject.h"
class Image;
class Animator;
class CBossDoor : public CGameObject
{
public:
	CBossDoor();
	virtual ~CBossDoor();

	CAnimator* m_pAnimator;
	CImage* m_DoorImage;

	bool door;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider);
	void OnCollisionStay(CCollider* pOtherCollider);
	void OnCollisionExit(CCollider* pOtherCollider);
};

