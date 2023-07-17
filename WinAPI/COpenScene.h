#pragma once
#include "CSceneOpen.h"

class COpenScene : public CScene
{
public:
	COpenScene();
	virtual ~COpenScene();

private:
	CSceneOpen* open;
	CSound* StageOpenSound;

private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};

