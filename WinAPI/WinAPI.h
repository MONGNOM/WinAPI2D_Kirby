#pragma once

#include "resource.h"

//========================================
//##    전역변수(인스턴스, 윈도우 핸들)	##
//========================================

extern HINSTANCE hInst;
extern HWND hWnd;

//========================================
//##			윈도우 설정				##
//========================================

#define WINSTARTX   100
#define WINSTARTY   100
#define WINSIZEX	800
#define	WINSIZEY	600
#define WINSTYLE	WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

//========================================
//##			게임씬 그룹				##
//========================================

enum class GroupScene
{
	Title,

	TileTool,

	Opne,

	Stage01,
	
	Bonus,

	Stage02,

	End,

	Size,
};

//========================================
//##				레이어				##
//========================================

enum class Layer
{
	Default,
	Tile,
	Wall,
	Item,
	Door,
	Monster,
	ChangeFormStar,
	Player,
	Weapon,
	MWeapon,
	Eat,
	HitCollider,
	Missile,
	Ice,
	Effect,
	Star,
	Ui,
	Panel,
	Size,
};

//========================================
//##				타일					##
//========================================

enum class TypeTile
{
	None,
	Ground,
	Platform,
	Wall,

	Size,
};

