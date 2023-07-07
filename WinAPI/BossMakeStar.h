#pragma once
#include "CGameObject.h"
#include "CEffect.h"

class Image;
class Animator;

class BossMakeStar : public CGameObject
{

public:
	float starTimer;
	BossMakeStar();
	virtual ~BossMakeStar();


	CAnimator* m_pAnimator;
	CImage* m_pstarImage;
	CEffect* effect;

public:
	
	void StarMaker(); // ��ġ�� ��������
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void OnCollisionEnter(CCollider* pOtherCollider);
	void OnCollisionStay(CCollider* pOtherCollider) ;

};

