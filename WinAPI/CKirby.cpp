#include "framework.h"
#include "CKirby.h"
#include "CGameManager.h"
#include "CKirbyHp.h"
#include "CEventManager.h"

CKirby::CKirby()
{
/* �޸���
	
	���� ���� �� ����:
	=========================================================
	������ ������ �ڷ� �����°� �߰�������� + ���� �ִϸ��̼� �߰�
	���� Ǯ���� �߰� <����� ���ư���>
	������ ����ȭ��߰� ��ư������ ����
	�������� ��ġ������ ����� ����� �԰� �������ְ�
	=============================================================
	���� �ϸ� ���߰�  ȭ�� ��İ��ϰ� �ڼ� ��� �ִϸ��̼� �߰�
	���� �ִϸ��̼� �״� ����?
	=================================================================
	���۾ִϸ��̼� ĸó ������ �ᵵ �� ��?
	���۽� ��Ÿ�� �ͼ� ������
	
	������ �� ��
	
	Ŀ��
	�븻��ų ����������Ʈ �߰�
	�޸��� �Ҷ� ����Ʈ �߰�
 
	���� && ����
	���̽� ���� ����Ʈ
	���������� ������ ����Ʈ�߰� = �̹��� �߶� �ؾ���
	================================================================
	���� ����:
	�ٴڶձ�, ���ձ� => ������ �ҽ� ������ ���� = [���� ��]
*/ 

	playerHp = GAME->curHp;
	m_fSpeed = 0.f;
	m_jumpSpeed = 0.f;
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Player;
	m_strName = L"Ŀ��";
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
	if (pOtherCollider->GetObjName() == L"�ٴ�")
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
	if (pOtherCollider->GetObjName() == L"�ٴ�")
	{
		--m_groundCounter;
		if (m_groundCounter <= 0)
		{
			m_groundchecker = false;
		}
	}
}
