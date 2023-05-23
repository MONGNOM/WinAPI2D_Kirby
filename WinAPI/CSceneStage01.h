#pragma once
#include "CScene.h"
#include "CKirby.h"
#include "CNomalKirby.h"

class CSceneStage01 : public CScene
{
public:
	CSceneStage01();
	virtual ~CSceneStage01();

private:
	CNomalKirby* pkirby;
private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
