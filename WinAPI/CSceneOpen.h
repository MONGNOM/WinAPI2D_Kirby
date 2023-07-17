#pragma once
#include "CGameObject.h"
class CSceneOpen : public CGameObject
{
public:
	CSceneOpen();
	virtual~CSceneOpen();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	CImage* OpenImage1;
	CImage* OpenImage2;
	CImage* OpenImage3;
	CImage* OpenImage4;
	CImage* OpenImage5;
	CImage* OpenImage6;
	CImage* OpenImage7;
	CImage* OpenImage8;
	CImage* OpenImage9;

	float openSceneTimer;

	queue<CImage*> m_queOpenImage;
};

