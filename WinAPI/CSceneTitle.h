#pragma once
#include "CScene.h"
#include "CSceneOpen.h"

class CSceneTitle : public CScene
{
public:
	CSceneTitle();
	virtual ~CSceneTitle();

	CSound* TitleSound;
	CSound* ClickSound;
	CSceneOpen* open;

private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
