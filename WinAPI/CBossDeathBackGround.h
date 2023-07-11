#pragma once
#include "CGameObject.h"

class Image;
class Animator;


class CBossDeathBackGround :public CGameObject
{
public:
	CBossDeathBackGround();
	virtual ~CBossDeathBackGround();

	bool Destory;
	float DestoryTime;

private:
	CImage* m_pBossDeathBackGround;

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

};

