#pragma once
#include "CScene.h"
#include "CNomalKirby.h"
#include "CIceKirby.h"
#include "CSwordKirby.h"
#include "CBossMonster.h"
#include "CBossDeathBackGround.h"

class Image;
class Animaotr;

class CSceneState02 : public CScene
{
public:
	CSceneState02();
	virtual ~CSceneState02();


private:

	float cameraTimer;
	CBossMonster* bossMonster;
	CNomalKirby* pkirby;
	CSound* BossBGMSound;
	CSound* ClickSound;
	CBossDeathBackGround* bossDeathBackGround;


private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};

