#pragma once
#include "CUI.h"
class CKirbyHp : public CUI
{
public:
	CKirbyHp();
	virtual~CKirbyHp();
private:
	CImage* GaugehpImage;
	CImage* FramehpImage;

	void OnMouseEnter();
	void OnMouseOver();
	void OnMouseExit();
	void OnMouseUp();
	void OnMouseDown();
	void OnMouseClicked();
public:

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

