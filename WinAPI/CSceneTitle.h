#pragma once
#include "CScene.h"

class CSceneTitle : public CScene
{
public:
	CSceneTitle();
	virtual ~CSceneTitle();
	CSound* BackGroundSound1;
	CSound* BackGroundSound12;

private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
