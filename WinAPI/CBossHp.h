#pragma once
#include "CUI.h"
class CBossHp : public CUI
{

public:
	CBossHp();
	virtual~CBossHp();

private:


	CImage* HpImage;

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

