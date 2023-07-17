#pragma once
class EndingScene : public CGameObject
{
public:
	EndingScene();
	virtual ~EndingScene();

private:

	void Init()		override;
	void Update()	override;
	void Render()	override;
	void Release()	override;


	CImage* endImage;
	CImage* endImage1;
	CImage* endImage2;
	CImage* endImage3;
	CImage* endImage4;
	CImage* endImage5;
	CImage* endImage6;
	CImage* endImage7;
	CImage* endImage8;
	CImage* endImage9;
	CImage* endImage10;

	float endSceneTimer;

	queue<CImage*> m_queEndImage;

};

