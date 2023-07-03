#pragma once
#include "CGameObject.h"
class CBackGround : public CGameObject
{
public:

	CBackGround();
	virtual ~CBackGround();

private:
	CImage* m_pStage1BackGroundImage;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

