#include "framework.h"
#include "EndingScene.h"

EndingScene::EndingScene()
{
	endImage = RESOURCE->LoadImg(L"Kirbyend11", L"Image\\Animation\\end\\0.png");
	endImage1 = RESOURCE->LoadImg(L"Kirbyend1", L"Image\\Animation\\end\\1.png");
	endImage2 = RESOURCE->LoadImg(L"Kirbyend2", L"Image\\Animation\\end\\2.png");
	endImage3 = RESOURCE->LoadImg(L"Kirbyend3", L"Image\\Animation\\end\\3.png");
	endImage4 = RESOURCE->LoadImg(L"Kirbyend4", L"Image\\Animation\\end\\4.png");
	endImage5 = RESOURCE->LoadImg(L"Kirbyend5", L"Image\\Animation\\end\\5.png");
	endImage6 = RESOURCE->LoadImg(L"Kirbyend6", L"Image\\Animation\\end\\6.png");
	endImage7 = RESOURCE->LoadImg(L"Kirbyend7", L"Image\\Animation\\end\\7.png");
	endImage8 = RESOURCE->LoadImg(L"Kirbyend8", L"Image\\Animation\\end\\8.png");
	endImage9 = RESOURCE->LoadImg(L"Kirbyend9", L"Image\\Animation\\end\\9.png");
	endImage10 = RESOURCE->LoadImg(L"Kirbyend10", L"Image\\Animation\\end\\10.png");
	endSceneTimer = 0;

}

EndingScene::~EndingScene()
{
}

void EndingScene::Init()
{

	m_queEndImage.push(endImage);
	m_queEndImage.push(endImage1);
	m_queEndImage.push(endImage2);
	m_queEndImage.push(endImage3);
	m_queEndImage.push(endImage4);
	m_queEndImage.push(endImage5);
	m_queEndImage.push(endImage6);
	m_queEndImage.push(endImage7);
	m_queEndImage.push(endImage8);
	m_queEndImage.push(endImage9);
	m_queEndImage.push(endImage10);
}



void EndingScene::Update()
{

	endSceneTimer += DT;
	if (endSceneTimer > 2.5f)
	{
		m_queEndImage.pop();
		endSceneTimer = 0;
	}
	if (m_queEndImage.size() == 1)
	{
		CAMERA->FadeOut(0.7f);
		DELAYCHANGESCENE(GroupScene::Title, 2.5f);
	}
}

void EndingScene::Render()
{
	RENDER->Image(m_queEndImage.front(), 0, 0, 800, 600);;

}



void EndingScene::Release()
{
}
