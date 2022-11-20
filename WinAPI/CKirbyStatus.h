#pragma once
#include "CUI.h"
class CKirbyStatus : public CUI
{
public:
	CKirbyStatus();
	virtual~CKirbyStatus();

private:


	CImage* StatusImage;
	CImage* StatusImageIce;
	CImage* StatusImageIceMark;
	CImage* StatusImageLight;
	CImage* StatusImageLightMark;

public:



	void SetHp();

	void OnMouseEnter();
	void OnMouseOver();
	void OnMouseExit();
	void OnMouseUp();
	void OnMouseDown();
	void OnMouseClicked();


	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};


