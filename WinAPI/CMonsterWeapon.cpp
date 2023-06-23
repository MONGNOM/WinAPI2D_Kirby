#include "framework.h"
#include "CMonsterWeapon.h"

CMonsterWeapon::CMonsterWeapon()
{
	m_layer = Layer::MWeapon;
	m_strName = L"몬스터무기";
	colliderX = 50;
	colliderY = 50;

}

CMonsterWeapon::~CMonsterWeapon()
{
}

void CMonsterWeapon::SetMonsterWeaponScale(float x, float y)
{
	colliderX = x;
	colliderY = y;

}

void CMonsterWeapon::Init()
{
	AddCollider(ColliderType::Rect, Vector(colliderX, colliderY), Vector(0, 0));

}

void CMonsterWeapon::Update()
{
}

void CMonsterWeapon::Render()
{
}

void CMonsterWeapon::Release()
{
}
