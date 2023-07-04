#include "framework.h"
#include "CKirby.h"
#include "CGameManager.h"
#include "CKirbyHp.h"
#include "CEventManager.h"

CKirby::CKirby()
{
/* 메모장
	
	내일 구현 할 내용:
	=========================================================
	데미지 받으면 뒤로 굴르는거 추가해줘야함 + 무적 애니메이션 추가
	변신 풀리는 추가 <별모양 날아가게>
	변신후 설명화면뜨고 버튼누르면 꺼짐
	보스몬스터 망치찍을때 별모양 만들고 먹고 뱉을수있게
	=============================================================
	변신 하면 멈추고  화면 까맣게하고 자세 잡는 애니메이션 추가
	보스 애니메이션 죽는 수정?
	=================================================================
	시작애니메이션 캡처 본으로 써도 될 듯?
	시작시 별타고 와서 착지함
	
	집가서 할 것
	
	커비
	노말스킬 터지는이펙트 추가
	달리기 할때 이팩트 추가
 
	보스 && 몬스터
	아이스 데스 이펙트
	보스데미지 받을때 이펙트추가 = 이미지 잘라서 해야함
	================================================================
	수정 사항:
	바닥뚫기, 벽뚫기 => 교수님 소스 가져다 쓰기 = [거의 완]
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

	
}

void CKirby::Render()
{
}

void CKirby::Release()
{
}

void CKirby::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"바닥")
	{
		m_groundCounter++;
		m_groundchecker = true;
	}
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Monster)
	{
		SOUND->Play(DamageSound, 0.1f, false);
		if (GAME->HpNotDown == true)
		{
			playerHp -= 0;
		}
		else
		{
			playerHp -= 1;
		}
		GAME->PlayerHit = true;
	}
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::MWeapon)
	{
		SOUND->Play(DamageSound, 0.1f, false);
		if (GAME->HpNotDown == true)
		{
			playerHp -= 0;
		}
		else
		{
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
	if (pOtherCollider->GetObjName() == L"바닥")
	{
		--m_groundCounter;
		if (m_groundCounter <= 0)
		{
			m_groundchecker = false;
		}
	}
}
