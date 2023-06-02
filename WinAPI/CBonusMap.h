#pragma once
#include "CScene.h"
#include "CItem.h"
#include "CPersimmon.h"


class CBonusMap : public CScene
{
public:
	CBonusMap();
	virtual ~CBonusMap();

	CPersimmon* pPersimon;
private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};

