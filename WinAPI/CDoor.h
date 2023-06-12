#pragma once
#include "CGameObject.h"

class Image;
class Animator;

class CDoor : public CGameObject
{
public:
	CDoor();
	virtual ~CDoor();

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

