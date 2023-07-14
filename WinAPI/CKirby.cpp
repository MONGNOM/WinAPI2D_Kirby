#include "framework.h"
#include "CKirby.h"
#include "CGameManager.h"
#include "CKirbyHp.h"
#include "CEventManager.h"

CKirby::CKirby()
{
/* 메모장
	
	보류 (애매한 작업들)
	=========================================================
	보스데미지 받을때 이펙트추가 = 시간차에따라 생겨줘야할듯? --> 포기; 나중에 여쭤보기

	=========================================================

	구현 할 내용:
	=========================================================
	
	1. 시작애니메이션 캡처 본으로 써도 될 듯 = 백터 저장해서 꺼내주면 될 것 같음 ?일단 다 자름? [반 완] 엔딩부분짤라야함 ㅇㅈ?
	ㄴ 보스 죽으면 씬 전환으로 애니메이션 틀어주고 애니메이션 끝나면 타이틀 화면 ㄱ
	
	보스 점프 공격후 카메라 떨림 구현 못함 판단하나만 더해주면 될듯;
	================================================================
*/ 


	playerHp = GAME->curHp;
	m_fSpeed = 0.f;
	m_jumpSpeed = 0.f;
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Player;
	m_strName = L"커비";
	m_groundchecker = false;
	m_vecMoveDir = Vector(1, 0);
	m_vecLookDir = Vector(0, 0);
	lastLeftInputTime = 10;
	lastRightInputTime = 10;
	fallTimer = 0;
	flyTimer = 0;
	m_groundCounter = 0;
	m_gravity = 300;
	stage1 = true;
	m_panelOneCoin = true;
	m_formChangeTimer = 0;
}

CKirby::~CKirby()
{
}

void CKirby::Init()
{
	hp = new CKirbyHp();
	hp->SetPos(110, 550);
	hp->SetScale(270, 50);
	ADDOBJECT(hp);

	DamageSound		= RESOURCE->LoadSound(L"CDamageSound",	L"Sound\\Damage.wav");
	FlySound		= RESOURCE->LoadSound(L"FlySound",		L"Sound\\Fly.wav");
	
	JumpSound		= RESOURCE->LoadSound(L"JumpSound",		L"Sound\\Jump.wav");
	RunSound		= RESOURCE->LoadSound(L"RunSound",		L"Sound\\Run.wav");
	TeleportSound	= RESOURCE->LoadSound(L"TeleportSound", L"Sound\\Teleport.wav");
}



void CKirby::Effect(float x)
{
	effect = new CEffect();
	effect->SetPos(x, m_vecPos.y);
	ADDOBJECT(effect);
}

void CKirby::SelectSound(CSound* pSound, float volume, bool loop)
{
	SOUND->Play(pSound, volume, loop);
}

void CKirby::Update()
{
	
	GAME->playerLoockDirX = m_vecLookDir.x;
	GAME->playerPos = m_vecPos;
	GAME->curHp = playerHp;
	m_jumpSpeed -= m_gravity * DT;
	fallTimer += DT;
	lastLeftInputTime += DT;
	lastRightInputTime += DT;
	m_vecLookDir = m_vecMoveDir;
	if (!m_panelOneCoin)
	{
		Logger::Debug(L"123");
	}
	
}

void CKirby::Render()
{
}

void CKirby::Release()
{
}

void CKirby::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer()== Layer::Wall)
	{
		m_groundCounter++;
		m_groundchecker = true;
	}
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Monster)
	{
		if (GAME->HpNotDown == true)
		{
			playerHp -= 0;
		}
		else
		{
		SOUND->Play(DamageSound, 0.1f, false);
			playerHp -= 1;
		}
		GAME->PlayerHit = true;
	}
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::MWeapon)
	{
		if (GAME->HpNotDown == true)
		{
			playerHp -= 0;
		}
		else
		{
		SOUND->Play(DamageSound, 0.1f, false);
			playerHp -= 1;
		}
		GAME->PlayerHit = true;
	}
}

void CKirby::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CKirby::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Wall)
	{
		--m_groundCounter;
		if (m_groundCounter <= 0)
		{
			m_groundchecker = false;
		}
	}
}
