#pragma once
#include "CUI.h"
class CBossHp : public CUI
{
public:
	CBossHp();
	virtual~CBossHp();

private:
	CImage* m_pBossGaugeHpImage;
	CImage* m_pBossFrameHpImage;
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

