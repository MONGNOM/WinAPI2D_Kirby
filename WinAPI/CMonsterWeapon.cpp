#include "framework.h"
#include "CMonsterWeapon.h"

CMonsterWeapon::CMonsterWeapon()
{
	m_layer = Layer::MWeapon;
	m_strName = L"���͹���";
}

CMonsterWeapon::~CMonsterWeapon()
{
}

void CMonsterWeapon::Init()
{
	AddCollider(ColliderType::Rect, Vector(10, 10), Vector(0, 0));

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
