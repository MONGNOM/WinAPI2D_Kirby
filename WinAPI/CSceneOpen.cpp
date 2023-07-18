#include "framework.h"
#include "CSceneOpen.h"

CSceneOpen::CSceneOpen()
{
	OpenImage1 = RESOURCE->LoadImg(L"Kirbyopen1", L"Image\\Animation\\open\\1.png");
	OpenImage2 = RESOURCE->LoadImg(L"Kirbyopen2", L"Image\\Animation\\open\\2.png");
	OpenImage3 = RESOURCE->LoadImg(L"Kirbyopen3", L"Image\\Animation\\open\\3.png");
	OpenImage4 = RESOURCE->LoadImg(L"Kirbyopen4", L"Image\\Animation\\open\\4.png");
	OpenImage5 = RESOURCE->LoadImg(L"Kirbyopen5", L"Image\\Animation\\open\\5.png");
	OpenImage6 = RESOURCE->LoadImg(L"Kirbyopen6", L"Image\\Animation\\open\\6.png");
	OpenImage7 = RESOURCE->LoadImg(L"Kirbyopen7", L"Image\\Animation\\open\\7.png");
	OpenImage8 = RESOURCE->LoadImg(L"Kirbyopen8", L"Image\\Animation\\open\\8.png");
	OpenImage9 = RESOURCE->LoadImg(L"Kirbyopen9", L"Image\\Animation\\open\\9.png");
	openSceneTimer = 0;
}

CSceneOpen::~CSceneOpen()
{
}

void CSceneOpen::Init()
{
	m_queOpenImage.push(OpenImage1);
	m_queOpenImage.push(OpenImage2);
	m_queOpenImage.push(OpenImage3);
	m_queOpenImage.push(OpenImage4);
	m_queOpenImage.push(OpenImage5);
	m_queOpenImage.push(OpenImage6);
	m_queOpenImage.push(OpenImage7);
	m_queOpenImage.push(OpenImage8);
	m_queOpenImage.push(OpenImage9);
}

void CSceneOpen::Update()
{
	openSceneTimer += DT;
	if (openSceneTimer> 2.5f)
	{
		m_queOpenImage.pop();
		openSceneTimer = 0;
	}

	if (m_queOpenImage.size() == 1)
	{
		CAMERA->FadeOut(0.7f);
		DELAYCHANGESCENE(GroupScene::Stage01, 2.5f);
	}
}

void CSceneOpen::Render()
{
	RENDER->Image(m_queOpenImage.front(), 0, 0, 800, 600);;

	/* น้ลอ for (int i = 0; i < m_queOpenImage.size(); i++)
	{
		RENDER->Image(m_queOpenImage.at(i), 0, 0, 800, 600);;
	}
	RENDER->Image(OpenImage2, 0, 0, 800, 600);
	RENDER->Image(OpenImage3, 0, 0, 800, 600);
	RENDER->Image(OpenImage4, 0, 0, 800, 600);
	RENDER->Image(OpenImage5, 0, 0, 800, 600);
	RENDER->Image(OpenImage6, 0, 0, 800, 600);
	RENDER->Image(OpenImage7, 0, 0, 800, 600);
	RENDER->Image(OpenImage8, 0, 0, 800, 600);
	RENDER->Image(OpenImage9, 0, 0, 800, 600);*/
}

void CSceneOpen::Release()
{
}
