#include "framework.h"
#include "CBossDeathBackGround.h"

CBossDeathBackGround::CBossDeathBackGround()
{
	Destory = false;
	DestoryTime = 0;
	m_vecPos = Vector(0, 0);
	m_pBossDeathBackGround = nullptr;
}

CBossDeathBackGround::~CBossDeathBackGround()
{
}

void CBossDeathBackGround::Init()
{
	m_pBossDeathBackGround = RESOURCE->LoadImg(L"BbackGround2", L"Image\\Stage2_Clear.png");
}

void CBossDeathBackGround::Update()
{
	DestoryTime += DT;
	if (DestoryTime > 1.2f)
	{
		DELETEOBJECT(this);
	}
	
}


void CBossDeathBackGround::Render()
{
	RENDER->Image(m_pBossDeathBackGround, 0,0,800,600);
}

void CBossDeathBackGround::Release()
{
}

