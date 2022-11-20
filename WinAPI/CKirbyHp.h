#pragma once
#include "CUI.h"

class CPlayer;
 
class CKirbyHp : public CUI
{
	friend CPlayer;
public:
	CKirbyHp();
	virtual~CKirbyHp();

private:


	CAnimator* m_pAnimator;
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

