#pragma once
#include "CScene.h"
#include "CNomalKirby.h"
#include "CIceKirby.h"
#include "CSwordKirby.h"
#include "CBasicMonster.h"

class CSceneStage01 : public CScene
{
public:
	CSceneStage01();
	virtual ~CSceneStage01();

private:
	CBasicMonster* pBasicMonster;
	CNomalKirby* pkirby;
	CIceKirby* icekirby;
	CSwordKirby* swordkirby;
private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
