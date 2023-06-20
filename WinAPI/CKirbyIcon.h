#pragma once
#include "CUI.h"
#include "CNomalKirby.h"

class CNomalKirby;

class CKirbyIcon : public CUI
{
public:
	CKirbyIcon();
	virtual~CKirbyIcon();

private:

	CImage* StatusImage;
	CImage* StatusImageIce;
	CImage* StatusImageIceMark;
	CImage* StatusImageSword;
	CImage* StatusImageSwordMark;

public:
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

