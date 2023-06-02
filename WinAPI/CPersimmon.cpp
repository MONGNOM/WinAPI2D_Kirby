#include "framework.h"
#include "CPersimmon.h"
#include "CImageObject.h"
#include "CEventManager.h"

CPersimmon::CPersimmon()
{
}

CPersimmon::~CPersimmon()
{
}

void CPersimmon::Init()
{
	CImageObject* Persimmon = new CImageObject();
	Persimmon->SetImage(RESOURCE->LoadImg(L"Persimmon", L"Image\\Persimmon.png"));
	Persimmon->SetPos(400, 300);
	ADDOBJECT(Persimmon);

	AddCollider(ColliderType::Rect, Vector(50, 50), Vector(0, 0));
}

void CPersimmon::Update()
{

}

void CPersimmon::Render()
{
}

void CPersimmon::Release()
{
}
