#include "framework.h"
#include "CPlayer.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"
#include "CMonster.h"

#include "CMissile.h"
#include "KirbyEat.h"
#include "KirbyShot.h"
#include "CLightKirby.h"






CPlayer::CPlayer()
{
	ontile = 0;
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Player;
	m_strName = L"ÇÃ·¹ÀÌ¾î";

	m_Eat = true;
	m_pIdleImageR = nullptr;
	m_pIdleImageD = nullptr;
	m_pIdleImageU = nullptr;
	m_pIdleImageL = nullptr;
	m_pMoveImageR = nullptr;
	m_pMoveImageL = nullptr;
	m_pAttackImage = nullptr;

	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_bIsMove = false;
	Jumpgo = false;
	JumpTime = 0.f;
	m_Basic = true;

	m_LightChange = false;
	LastJumpTime = 0.f;
	LastRunTime;
	m_Gravity = true;
	m_pChangeImage = nullptr;
	LightKirby = nullptr;
	
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	m_pIdleImageR = RESOURCE->LoadImg(L"PlayerIdleR", L"Image\\KirbyIdleR.png");
	m_pIdleImageD = RESOURCE->LoadImg(L"PlayerIdleD", L"Image\\KirbyIdleR.png");
	m_pIdleImageU = RESOURCE->LoadImg(L"PlayerIdleU", L"Image\\KirbyIdleR.png");
	m_pIdleImageL = RESOURCE->LoadImg(L"PlayerIdleL", L"Image\\KirbyIdleL.png");
	m_pMoveImageR = RESOURCE->LoadImg(L"PlayerMoveR", L"Image\\KirbyRW.png");
	m_pMoveImageL = RESOURCE->LoadImg(L"PlayerMoveL", L"Image\\KirbyLW.png");
	m_pAttackImage = RESOURCE->LoadImg(L"PlayerAttack", L"Image\\iceRA.png");
	
	// Ä³¸¯ÅÍ 45x43ÇÈ¼¿
	
	m_pAnimator = new CAnimator;
		m_pAnimator->CreateAnimation(L"IdleUp", m_pIdleImageD, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleRight", m_pIdleImageD, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleDown", m_pIdleImageD, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleLeft", m_pIdleImageL, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);

		m_pAnimator->CreateAnimation(L"MoveUp", m_pMoveImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveRight", m_pMoveImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveDown", m_pMoveImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveLeft", m_pMoveImageL, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);

		m_pAnimator->CreateAnimation(L"IdleRightAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 0.03f, 1);
		m_pAnimator->CreateAnimation(L"IdleLeftAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleDownAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleUpAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);

		m_pAnimator->CreateAnimation(L"MoveRightAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(10.f, 10.f), Vector(45.f, 0.f), 10.0f, 3);
		m_pAnimator->CreateAnimation(L"MoveLeftAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"MoveUpAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"MoveDownAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);


	m_pAnimator->Play(L"IdleUp", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(45, 45), Vector(0, 0));
}

void CPlayer::Update()
{
	Gravity();
	m_bIsMove = false;

	//======º¸·ù ¸í´Ü=======
	// 1. ´Þ¸®±â ±¸Çö
	// ¤¤ ¿ÞÂÊ	 [-> + ->]
	// ¤¤ ¿À¸¥ÂÊ  [<- + <-]

	// 2. ¸Ô±â ¿À·ù 
	// ¤¤ ÇÃ·¹ÀÌ¾î°¡ ´ê´Â ÆÇÁ¤À» ¾î¶²°É·Î ¹Ù²ã¾ßÇÔ
	
	// 3. º®°ú ¶¥ Å¸ÀÏ ±¸ºÐ == ¹Ø, À§ ¿ÞÂÊ¿¡¼­ Ãæµ¹½Ã Ã¨ÇÇ¾ð À§Ä¡ x+ µÇ´Â°Å ÇØ°á ¹Ù¶÷
	//======================
	
	//========[Á¦ÀÏ Áß¿äÇÑ ±¸Çö]º¯½Å===========
	// ¤¤ º¯½Å ½Ã½ºÅÛÀ» º¯½Å ÇÒ ¶§ [ÀÏ¹Ý ÇÃ·¹ÀÌ¾î ÀÛµ¿ ºÒ·Î ´Ù ¸ØÃã] ==> º¯½Å Ç®¸®¸é º¯½Å ÇÃ·¹ÀÌ¾î ¸ØÃã
	// ¤¤ ½ºÅ×ÀÌÁö 1¿¡¼­ ÀÏ¹ÝÇÃ·¹ÀÌ¾î[ÀÏ¹ÝÄ¿ºñ]¸¦ »èÁ¦ ÇÒ ¶§ ´Ù¸¥ Å¬·¡½ºÀÇ ÇÃ·¹ÀÌ¾î¸¦ Ãß°¡[ºûÄ¿ºñ]
	// ºûÀ¸·Î º¯½ÅÇßÀ»¶§ °ø°ÝÀ» ¾ÈÇÑ´Ù. ???
	
	//========================================
	
	//======ÇØ¾ß ÇÒ ¸í´Ü=======
	// 5. ±âº» ==> º¯½Å ÀÌ¹ÌÁö ¹Ù²Ü¼ö ÀÖ°Ô ÇØÁà¾ßÇÏ´Âµ¥ ==> ¸ð¸£°Úµû
	// 6. º¸½º ¸¸µé±â
	// 6.5 ¸Ê »çÀÌÁî Á¤ÇÏ°í ±× À§Ä¡ ÀÌÈÄ´Â Ä«¸Þ¶ó Å¸ÄÏÆÃ ³¯¸®°í ±× ¹üÀ§ ¾ÈÀ¸·Î ¿À¸é ´Ù½Ã Ã¨ÇÇ¾ð °íÁ¤
	// 7. »óÈ£ÀÛ¿ë[¾ÆÀÌÅÛ] 
	// 7.5. º¸·ù 
	// 8. Ä¿ºñ ¸®¼Ò½º Å©±â ¼öÁ¤ == ÄíÆÄº¸´Ù Á¶±Ý ´õ Å©°Ô ¤¡ ÀÌ¹ÌÁö ÀÔÈ÷±â Å©±â : x: 96ÇÈ¼¿ y: 64ÇÈ¼¿
	//=========================
	
<<<<<<< HEAD
	======ÇØ¾ß ÇÒ ¸í´Ü=======
	 11. º¸½º½ºÅ×ÀÌÁö ³Ñ¾î°¥¶§ °ÔÀÓ¸Å´ÏÀú¿¡¼­ °¡Á®°¥±î?
	 12. º¸½º Á×ÀÌ¸é ¿µ»ó
	 13. ³»°¡ Á×À¸¸é ¾îÄ¯?
	 14. º¸·ù 
	========================
	¤¤
	=======ÁøÇàÁß========
	 8. º¸½º¸Ê & ¸Ê ¼öÁ¤Å©±â
	 9. UI ¸¸µé±â == Ã¼·Â¹Ù ±ðÀÌ´Â °Å ¤¡
 	 11. Å¸ÀÌÆ²È­¸é
	=====================
=======
	//=======ÁøÇàÁß========
	// 3. Æ¯¼ö ¸ó½ºÅÍ ±¸Çö [¿Ï] == ºû¸¸¿Ï ¾óÀ½Ãß°¡¿¹Á¤
	// 4. º¯½Å ±â´É == ¾óÀ½ ÀÌ¶û ºû ½Ã°£µÇ¸é ºÒ ÇÏ°í ½ºÆÄÅ©
	// 5. º¯½Å ¹þ±â ¿ÀºêÁ§Æ® ¸¸µé°í ´Ù½Ã ¸ÔÀ¸¸é ´Ù½Ã º¯½Å ¤¡
	//=====================
>>>>>>> parent of 812e713 (feat : ë³´ìŠ¤ ëª¬ìŠ¤í„° ë° í”Œë ˆì´ì–´ ë³€ì‹  ë° ìƒí˜¸ìž‘ìš© ë¬¸ êµ¬í˜„)


	//======¿Ï¼º ¸í´Ü=======
	// 1. µÞ ¹è°æ , ¸Ê Å¸ÀÏ »çÀÌÁî ¸Â°Ô ¼öÁ¤ ¿ä¸Á ÁÙÀÌ¸é µÉµí Á¶±Ý¸¸ 32¹è¼ö·Î
	// 2. ÀÏ¹Ý ¸ó½ºÅÍ ±¸Çö
	// 3. Æ¯¼ö¸ó½ºÅÍ ±¸Çö 
	// 4. Èí¼ö ±â´É ¿Ï¼º
	// 5. º¯½Å ±â´É ¿Ï¼º
	// 6. º¯½Å ¹þ±â ±â´É ¿Ï¼º
	//=====================

<<<<<<< HEAD
	======¿Ï¼º ¸í´Ü=======
	 1. µÞ ¹è°æ , ¸Ê Å¸ÀÏ »çÀÌÁî ¸Â°Ô ¼öÁ¤ ¿ä¸Á ÁÙÀÌ¸é µÉµí Á¶±Ý¸¸ 32¹è¼ö·Î
	 2. ÀÏ¹Ý ¸ó½ºÅÍ ±¸Çö
	 3. Æ¯¼ö¸ó½ºÅÍ ±¸Çö 
	 4. Èí¼ö ±â´É ¿Ï¼º
	 5. º¯½Å ±â´É ¿Ï¼º
	 6. º¯½Å ¹þ±â ±â´É ¿Ï¼º
	 7. ¸ó½ºÅÍ ±¸Çö ¿Ï¼º [º¸½º ÀÏ¹Ý Æ¯º°]
	 8. »óÈ£ÀÛ¿ë[¹® == Æ¯Á¤¹öÆ°½Ã º¸½º¹æ]
	 9. ¾óÀ½Ä¿ºñ ¿Ï¼º 
	=====================
	*/

	GAME->PlayerPos = m_vecPos;

	if (m_pHp <= 0)
	{
		DELETEOBJECT(this);
	}
=======
>>>>>>> parent of 812e713 (feat : ë³´ìŠ¤ ëª¬ìŠ¤í„° ë° í”Œë ˆì´ì–´ ë³€ì‹  ë° ìƒí˜¸ìž‘ìš© ë¬¸ êµ¬í˜„)


	if (BUTTONSTAY(VK_LEFT))
	{
		LastRunTime += DT;
		if (BUTTONSTAY('R')/*LastRunTime <= 0.15f && BUTTONSTAY(VK_LEFT)*/)
		{
			m_vecPos.x -= m_fSpeed * DT * 2.f;
			m_bIsMove = true;
			m_vecMoveDir.x = -1;
			LastRunTime = 0;
		}
		else if (BUTTONSTAY('S'))
		{
			m_vecMoveDir.x = 0;
			m_bIsMove = false;
		}
		else
		{
			m_vecPos.x -= m_fSpeed * DT;
			m_bIsMove = true;
			m_vecMoveDir.x = -1;
		}
	}

	else if (BUTTONSTAY(VK_RIGHT))
	{
		
		if(BUTTONSTAY('R')/*LastRunTime <= 0.15f && BUTTONSTAY(VK_RIGHT)*/)
		{ 
			m_vecPos.x += m_fSpeed * DT *2.f;
			m_bIsMove = true;
			m_vecMoveDir.x = +1;
			LastRunTime = 0;
		}
		else if (BUTTONSTAY('S'))
		{
			m_vecMoveDir.x = 0;
			m_bIsMove = false;
		}
		else
		{
			m_vecPos.x += m_fSpeed * DT;
			m_bIsMove = true;
			m_vecMoveDir.x = +1;
		}
	}

	else
	{
		m_vecMoveDir.x = 0;
	}

	if (m_Eat == false && BUTTONDOWN(VK_DOWN))
	{
		Logger::Debug(L"Ä¿ºñ°¡ ¼ÒÈ­½ÃÄ×´Ù");
		m_Eat = true;

		if (m_LightChange == true)
		{
			Logger::Debug(L"Ä¿ºñ°¡ ºûÀ¸·Î º¯½ÅÇß´Ù");
			DeleteObject(this);
			m_Basic = false;
			ChangePlayer();
		}
		
	}


	if (BUTTONDOWN('S'))
	{
		if (m_Basic == true)
		{
			if (m_Eat)  //true
			{
				Eat();
			}
			else // false
			{
				Shot();
			}
		}

	}

	if (BUTTONDOWN('A'))
	{
		Jumpgo = true;
	}
<<<<<<< HEAD
	if (BUTTONSTAY(VK_UP))
	{
			JumpTime += DT;

			if (JumpTime <= 0.3f)
			{
				Logger::Debug(L"Á¡ÇÁ");
				m_vecPos.y -= m_fSpeed * DT * 3;
			}
			else
			{
				JumpTime = 0;
				Jumpgo = false;
			}
	}
=======
>>>>>>> parent of 812e713 (feat : ë³´ìŠ¤ ëª¬ìŠ¤í„° ë° í”Œë ˆì´ì–´ ë³€ì‹  ë° ìƒí˜¸ìž‘ìš© ë¬¸ êµ¬í˜„)


	if (Jumpgo == true)
	{
		JumpTime += DT;

		if (JumpTime <= 0.3f)
		{
			Logger::Debug(L"Á¡ÇÁ");
			m_vecPos.y -= m_fSpeed * DT * 4;
		}
		else
		{
			JumpTime = 0;
			Jumpgo = false;
		}
	}

		AnimatorUpdate();
}


void CPlayer::Gravity()
{
	if (m_Gravity == true)
		m_vecPos.y += m_fSpeed * DT * 2;
	

}
	
void CPlayer::Render()
{
}

void CPlayer::Release()
{
	
}


void CPlayer::AnimatorUpdate()
{
	if (m_vecMoveDir.Length() > 0)
		m_vecLookDir = m_vecMoveDir;

	wstring str = L"";
	
	if (m_bIsMove)	str += L"Move";
	else			str += L"Idle";

	if (m_vecLookDir.x > 0) str += L"Right";
	else if (m_vecLookDir.x < 0) str += L"Left";

	if (m_vecLookDir.y > 0) str += L"Up";
	else if (m_vecLookDir.y < 0) str += L"Down";


	if (BUTTONSTAY('S')) str += L"Attack";

	m_pAnimator->Play(str, false);
}

void CPlayer::Shot()
{
	Logger::Debug(L"Shot");
	KirbyShot* Shot = new KirbyShot;
	Shot->SetPos(m_vecPos);
	Shot->SetDir(Vector(m_vecLookDir.x, m_vecMoveDir.y));
	ADDOBJECT(Shot);
	m_Eat = true;
  
}

void CPlayer::ChangePlayer()
{
	CGameObject* lightKirby = new CLightKirby();
	lightKirby->SetPos(m_vecPos);
	ADDOBJECT(lightKirby);

	CAMERA->SetTargetObj(lightKirby);

	DELETEOBJECT(this);
}

void CPlayer::Eat()
{
	Logger::Debug(L"°ø°Ý¿ÀºêÁ§Æ® »ý¼º");

	KirbyEat* m_KE = new KirbyEat;
	if (m_vecLookDir.x > 0)
		m_KE->SetPos(m_vecPos.x + 30, GetPos().y);
	else if (m_vecLookDir.x < 0)
		m_KE->SetPos(m_vecPos.x - 30, GetPos().y);

	m_KE->SetDir(Vector(m_vecPos.x, m_vecMoveDir.y));
	ADDOBJECT(m_KE);
	// ´Ù¸¥ Å¬·¡½ºÀÇ ¿ÂÄÝ¸®ÀüÀÍ½ËÀ» °¡Á®¿Ã¼öÀÖ³ª
}



void CPlayer::OnCollisionEnter(CCollider* pOtherCollider)
{
	
	if (pOtherCollider->GetObjName() == L"¸ó½ºÅÍ")
	{
		Logger::Debug(L"¸ó½ºÅÍ¿Í ºÎµúÇô µ¥¹ÌÁö¸¦ ÀÔ½À´Ï´Ù.");
		m_LightChange = false;
		m_Eat = false;
	}

	if (pOtherCollider->GetObjName() == L"ºû¸ó½ºÅÍ")
	{
		Logger::Debug(L"¸ó½ºÅÍ¿Í ºÎµúÇô µ¥¹ÌÁö¸¦ ÀÔ½À´Ï´Ù.");
		m_LightChange = true;
		m_Eat = false;

	}
	
	if (pOtherCollider->GetObjName() == L"¸Ô±â")
	{
		Logger::Debug(L"¸ó½ºÅÍ¸¦ »ïÄ×´Ù?");
		CGameObject* Eat = pOtherCollider->GetOwner();
		
	}

	if (pOtherCollider->GetObjName() == L"¶¥")
	{
		if(ontile >= 1)
		m_Gravity = false;
		++ontile;
	}
}




void CPlayer::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"¶¥")
	{	
		if (ontile >= 1)
		m_Gravity = false;
	}
}

void CPlayer::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"¶¥")
	{
		--ontile;
		if (ontile == 0)
		{
			m_Gravity = true;
		}
	}
}



