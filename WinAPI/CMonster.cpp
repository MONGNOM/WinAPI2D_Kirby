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
	bosseffectTimer += DT;

	Logger::Debug(to_wstring(bosseffectTimer));
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

void CMonster::BossEffect()
{

	effect = new CEffect();
	effect->SetPos(m_vecPos.x, m_vecPos.y - 15);
	effect->BossAttackEffect();
	ADDOBJECT(effect);
	effect->effectDestory = true;

	if (bosseffectTimer > 0.27f)
	{
		bossEffect = new CEffect();
		bossEffect->SetPos(m_vecPos.x + 20, m_vecPos.y + 100);
		ADDOBJECT(bossEffect);
		bossEffect->BossAttackEffect();
		bossEffect->effectDestory = true;

	}

	if (bosseffectTimer > 0.54f)
	{

		bossEffect1 = new CEffect();
		bossEffect1->SetPos(m_vecPos.x - 50, m_vecPos.y + 20);
		ADDOBJECT(bossEffect1);
		bossEffect1->BossAttackEffect();
		bossEffect1->effectDestory = true;
	}

	if (bosseffectTimer > 0.81f)
	{
		bossEffect2 = new CEffect();
		bossEffect2->SetPos(m_vecPos.x, m_vecPos.y + 40);
		ADDOBJECT(bossEffect2);
		bossEffect2->BossAttackEffect();
		bossEffect2->effectDestory = true;
	}
	
		 
	 if (bosseffectTimer > 0.81f)
	{
		bossEffect2 = new CEffect();
		bossEffect2->SetPos(m_vecPos.x, m_vecPos.y + 40);
		ADDOBJECT(bossEffect2);
		bossEffect2->BossAttackEffect();
		bossEffect2->effectDestory = true;
	}
	 if (bosseffectTimer > 1.08f)
	{
		bossEffect3 = new CEffect();
		bossEffect3->SetPos(m_vecPos.x - 35, m_vecPos.y + 70);
		ADDOBJECT(bossEffect3);
		bossEffect3->BossAttackEffect();
		bossEffect3->effectDestory = true;
	}
	 if (bosseffectTimer > 1.35f)
	{
		bossEffect4 = new CEffect();
		bossEffect4->SetPos(m_vecPos.x + 50, m_vecPos.y + 55);
		ADDOBJECT(bossEffect4);
		bossEffect4->BossAttackEffect();
		bossEffect4->effectDestory = true;
	}
	 if (bosseffectTimer > 1.61f)
	{
		bossEffect5 = new CEffect();
		bossEffect5->SetPos(m_vecPos.x + 50, m_vecPos.y - 5);
		bossEffect5->BossAttackEffect();
		ADDOBJECT(bossEffect5);
		bossEffect5->effectDestory = true;
	}
	 if (bosseffectTimer > 1.88f)
	{
		bossEffect6 = new CEffect();
		bossEffect6->SetPos(m_vecPos.x - 30, m_vecPos.y + 50);
		ADDOBJECT(bossEffect6);
		bossEffect6->BossAttackEffect();
		bossEffect6->effectDestory = true;
		bosseffectTimer = 0;
	}


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
	else
	{
		//iceDie = false;
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
