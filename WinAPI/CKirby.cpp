#include "framework.h"
#include "CKirby.h"
#include "CGameManager.h"
#include "CKirbyHp.h"
#include "CEventManager.h"

CKirby::CKirby()
{
/* 메모장
	
	구현 내용:
	백그라운드배경 ->
	커비 포커즈 풀고 처음에 배경고정한다음 일정 거리 지나면 커비고정으로 바꾸고 배경을 스크롤링 해준다ㅇㅋ? 그럼 배경끝 

	애니메이션 추가할 것
	커비
	처음 먹었을때 이미지 추가
	1. 변신 풀리는 추가 <별모양 날아가게>
	2. 노말스킬 + 터지는이펙트 추가
	3. 변신 풀기 이펙트 추가
	4. 아이스 이펙트 교체
	5. 달리기 할때 이팩트 추가
	6. 무적 애니메이션 추가

	몬스터 죽는거 이펙트추가
	보스데미지 받을때 이펙트추가
	보스 애니메이션 죽는 수정?

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



void CKirby::SelectSound(CSound* pSound, float volume, bool loop)
{
	SOUND->Play(pSound, volume, loop);
}

void CKirby::Update()
{
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
