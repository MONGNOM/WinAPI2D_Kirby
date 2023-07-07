#pragma once
#include "CUI.h"

class CTransFormPanel :public CUI
{
public:

	CTransFormPanel();
	virtual ~CTransFormPanel();

private:

	
	float panelTimer;
	CImage* m_picemainImage;
	CImage* m_pswordmainImage;
	CSound* ClickSound;


	void PickPanel(wstring key);

	void OnMouseEnter();
	void OnMouseOver();
	void OnMouseExit();
	void OnMouseUp();
	void OnMouseDown();
	void OnMouseClicked();

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

