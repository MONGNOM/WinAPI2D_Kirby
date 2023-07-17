#pragma once
#include "CScene.h"
#include "EndingScene.h"
class CEndingStage : public CScene
{
public:
	CEndingStage();
	virtual ~CEndingStage();

	EndingScene* end;
	CSound* endSound;

private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;

};

