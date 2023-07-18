#include "framework.h"
#include "CMonster.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CKirbyWeapon.h"
#include "CNomalKirby.h"
#include "CMonsterAttackCollider.h"
#include "CMonsterWeapon.h"
#include "CGameManager.h"

CMonster::CMonster()
{
	collider = nullptr;
	m_layer = Layer::Monster;
	m_fSpeed = 200.f;
	m_vecLookDir = Vector(1, 0);
	m_groundchecker = false;
	m_groundCounter = 0;
	m_gravity = 300;
	dieTimer = 0;
	idleTimer = 0;
	attackTimer = 0;
	walkTimer = 0;
	hp = 0;
	dizzy = false;
	iceDie = false;
	DamageSound = RESOURCE->LoadSound(L"MonsterDamageSound", L"Sound\\Damage.wav");
	DeathSound	= RESOURCE->LoadSound(L"MonsterDeathSound", L"Sound\\MonsterDeath.wav");
	GAME->invincible = 0.5f;
	effect = nullptr;
	bossEffect  = nullptr;
	bossEffect1 = nullptr;
	bossEffect2 = nullptr;
	bossEffect3 = nullptr;
	bossEffect4 = nullptr;
	bossEffect5 = nullptr;
	bossEffect6 = nullptr;
	bosseffectTimer = 0;
	bosseffect = false;

}

CMonster::~CMonster()
{
}

void CMonster::Init()
{
	collider = new CHitCollider();
	collider->SetMonster(this);
	ADDOBJECT(collider);
}

void CMonster::Update()
{
	
}

void CMonster::Render()
{
	
}

void CMonster::Release()
{
}

void CMonster::TakeDamage(int damage)
{
	SOUND->Play(DamageSound, 0.1f, false);
	hp -= damage;
	dizzy = true;
}

void CMonster::Effect(float x, float y)
{
	effect = new CEffect();
	effect->SetPos(x,y);
	ADDOBJECT(effect);
}





CMonster* CMonster::GetMonster()
{
	return this;
}

void CMonster::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Wall)
	{
		m_groundCounter++;
		m_groundchecker = true;

		CTile* wall = (CTile*)pOtherCollider->GetOwner();
		if (wall->GetPos().x >= m_vecPos.x && wall->GetPos().y <= m_vecPos.y)
		{
			m_vecLookDir.x = -1;
		}
		else if (wall->GetPos().x <= m_vecPos.x && wall->GetPos().y <= m_vecPos.y)
		{
			m_vecLookDir.x = 1;
		}
	}

	if (pOtherCollider->GetObjName() == L"무기")
	{
		CKirbyWeapon* pWeapon = (CKirbyWeapon*)pOtherCollider->GetOwner();
		
		if (GAME->monsterhpnotDown == true)
		{
			hp -= 0;
		}
		else
		{
			TakeDamage(pWeapon->damage);
		}
		GAME->monsterHit = true;
	}
	
	
	
	if (pOtherCollider->GetObjName() == L"일반커비")
	{
		CNomalKirby* normalKirby = (CNomalKirby*)pOtherCollider->GetOwner();
		if (normalKirby->eat)
		{
			DELETEOBJECT(this);
			DELETEOBJECT(collider);
			SOUND->Play(DeathSound, 0.1f, false);
			normalKirby->eating = true;
		}
		
	}

}


void CMonster::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Eat)
	{ 
		dizzy = true;
		if (m_vecPos.x > pOtherCollider->GetOwner()->GetPos().x)
			m_vecPos.x -= 500 * DT;
		if (m_vecPos.x < pOtherCollider->GetOwner()->GetPos().x)
			m_vecPos.x += 500 * DT;
	}
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Ice)
	{
		iceDie = true;
		CKirbyWeapon* pWeapon = (CKirbyWeapon*)pOtherCollider->GetOwner();
		if (GAME->monsterhpnotDown == true)
		{
			hp -= 0;
		}
		else
		{
			TakeDamage(pWeapon->damage);
		}
		GAME->monsterHit = true;
	}

}

void CMonster::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Wall)
	{
		--m_groundCounter;
		if (m_groundCounter <= 0)
		{
			m_groundchecker = false;
			Logger::Debug(L"몬스터가 미사일과 충돌해제");
		}
	}
	if (pOtherCollider->GetObjName() == L"무기")
	{
		dizzy = false;
		Logger::Debug(L"커비와 충돌");
	}

}
