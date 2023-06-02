#include "framework.h"
#include "CImageObject.h"

#include "CRenderManager.h"

#include "CImage.h"

CImageObject::CImageObject()
{
	m_pImage = nullptr;
}

CImageObject::~CImageObject()
{
}

CImage* CImageObject::GetIamge()
{
    return m_pImage;
}

void CImageObject::SetImage(CImage* pImage)
{
	m_pImage = pImage;
}

void CImageObject::Init()
{
}

void CImageObject::Update()
{
}

void CImageObject::Render()
{
	if (nullptr != m_pImage)
	{
		RENDER->Image(m_pImage,
			m_vecPos.x,
			m_vecPos.y,
			m_vecPos.x + (float)m_pImage->GetWidth(),
			m_vecPos.y + (float)m_pImage->GetHeight()
		);
	}
}

void CImageObject::Release()
{
}
