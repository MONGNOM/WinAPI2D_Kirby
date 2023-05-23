#pragma once
#include "CScene.h"
#include "CNomalKirby.h"
#include "CIceKirby.h"

class CSceneStage01 : public CScene
{
public:
	CSceneStage01();
	virtual ~CSceneStage01();

private:
	CNomalKirby* pkirby;
	CIceKirby* icekirby;
private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
