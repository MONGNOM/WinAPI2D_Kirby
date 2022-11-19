#include "framework.h"
#include "CMonster.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CPlayer.h"

CMonster::CMonster()
{
	m_strName = L"¸ó½ºÅÍ";
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Monster;
	m_vecDir = Vector(0, 0);
	m_fVelocity = 300;
<<<<<<< HEAD
	m_mMoveImage = nullptr;
	m_mDieImage = nullptr;
	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_bIsMove = false;
	m_mHp = 1;
	DieTime = 0;
	HP = false;
	Iscrash = false;
	slide = false;
	slideTime = 0;
	
=======
>>>>>>> parent of 812e713 (feat : ë³´ìŠ¤ ëª¬ìŠ¤í„° ë° í”Œë ˆì´ì–´ ë³€ì‹  ë° ìƒí˜¸ì‘ìš© ë¬¸ êµ¬í˜„)
}

CMonster::~CMonster()
{
}

void CMonster::Init()
{
	AddCollider(ColliderType::Rect, Vector(90, 90), Vector(0, 0));
}

void CMonster::Update()
{
	Gravity();

	m_vecPos += m_vecDir * m_fVelocity * DT;

<<<<<<< HEAD
	if (Iscrash == true)
	{
		DieTime += DT;
		//if (DieTime >= 0.1)
		//{
		//	str = L"IdleLeftDie";
		//}
		if (DieTime >= 1)
		{
			DELETEOBJECT(this);
			DieTime = 0;
		}
	}

	if (slide == true)
	{
		slideTime += DT;
		if (slideTime <= 0.1f)
		{
			if (GAME->PlayerPos.x <= m_vecPos.x)
				m_vecPos.x += m_fSpeed * DT * 3;

			else if (GAME->PlayerPos.x >= m_vecPos.x)
				m_vecPos.x -= m_fSpeed * DT * 3;

			slideTime = 0;
		}
	}
=======

	
>>>>>>> parent of 812e713 (feat : ë³´ìŠ¤ ëª¬ìŠ¤í„° ë° í”Œë ˆì´ì–´ ë³€ì‹  ë° ìƒí˜¸ì‘ìš© ë¬¸ êµ¬í˜„)
}



void CMonster::Gravity()
{
	if (m_Gravity == true)
	{
		m_vecPos.y += m_fSpeed * DT * 2;
	}


}


void CMonster::Render()
{
	RENDER->FrameRect(
		m_vecPos.x - m_vecScale.x * 0.5f,
		m_vecPos.y - m_vecScale.y * 0.5f,
		m_vecPos.x + m_vecScale.x * 0.5f,
		m_vecPos.y + m_vecScale.y * 0.5f);
	
}

void CMonster::Release()
{
}

void CMonster::OnCollisionEnter(CCollider* pOtherCollider)
{
	
	if (pOtherCollider->GetObjName() == L"ÇÃ·¹ÀÌ¾î")
	{
		Logger::Debug(L"¸ó½ºÅÍ°¡ ÇÃ·¹ÀÌ¾î¿Í ºÎµúÇô µ¥¹ÌÁö¸¦ ÀÔ½À´Ï´Ù.");
<<<<<<< HEAD
	
		m_mHp -= 1;
		Iscrash = true;
		HP = true;
		slide = true;
	}

	if (pOtherCollider->GetObjName() == L"ºû °ø°İ")
	{
		Logger::Debug(L"¸ó½ºÅÍ°¡ ºû°ø°İÀ» ¸Â¾Ò½À´Ï´Ù.");
		slide = true;
		Iscrash = true;

=======
		DELETEOBJECT(this);
>>>>>>> parent of 812e713 (feat : ë³´ìŠ¤ ëª¬ìŠ¤í„° ë° í”Œë ˆì´ì–´ ë³€ì‹  ë° ìƒí˜¸ì‘ìš© ë¬¸ êµ¬í˜„)
	}

	if (pOtherCollider->GetObjName() == L"¸Ô±â")
	{
		Logger::Debug(L"¸ó½ºÅÍ°¡ »¡·Á°¡±â ½ÃÀÛÇÕ´Ï´Ù.");
		CGameObject* pl = pOtherCollider->GetOwner();
		if(pl->GetPos().x <= m_vecPos.x )
			SetDir(Vector(-1, 0));
		else if (pl->GetPos().x >= m_vecPos.x)
			SetDir(Vector(1, 0));	
	}

	if (pOtherCollider->GetObjName() == L"ºû °ø°İ")
	{
		Logger::Debug(L"¸ó½ºÅÍ°¡ ºû°ø°İÀ» ´çÇß½À´Ï´Ù.");
		DELETEOBJECT(this);
	}

	if (pOtherCollider->GetObjName() == L"Shot")
	{
		Logger::Debug(L"¸ó½ºÅÍ°¡ ¹Ì»çÀÏ¿¡ ¸Â¾Ò½À´Ï´Ù");
		DELETEOBJECT(this);
	}
	if (pOtherCollider->GetObjName() == L"¶¥")
	{

		m_Gravity = false;
	}
}

void CMonster::OnCollisionStay(CCollider* pOtherCollider)
{

	if (pOtherCollider->GetObjName() == L"¸Ô±â")
	{
		Logger::Debug(L"¸ó½ºÅÍ°¡ »¡·Áµé¾î°¡°íÀÖ½À´Ï´Ù.");
	}
	if (pOtherCollider->GetObjName() == L"¶¥")
	{

		m_Gravity = false;
	}
}

void CMonster::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"¸Ô±â")
	{
		CGameObject* eat = pOtherCollider->GetOwner();
		Logger::Debug(L"!@!@!@!2¸ó½ºÅÍ¸¦ ¸Ô´Â´Ù¾Æ¾Æ¾Æ!@!@!@!@");
		DELETEOBJECT(this);

	}

}

void CMonster::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CMonster::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
