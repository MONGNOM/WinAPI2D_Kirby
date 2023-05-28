#include "framework.h"
#include "CKirbyWeapon.h"
#include "CCollider.h"

CKirbyWeapon::CKirbyWeapon()
{
	m_vecScale = Vector(10, 10);
	m_layer = Layer::Weapon;
	m_strName = L"¹«±â";
	damage = 10;
}

CKirbyWeapon::~CKirbyWeapon()
{
}

void CKirbyWeapon::Init()
{
	AddCollider(ColliderType::Rect, Vector(10, 10), Vector(0, 0));
}

void CKirbyWeapon::Update()
{
	damage = 10;
}

void CKirbyWeapon::Render()
{
}

void CKirbyWeapon::Release()
{
}



void CKirbyWeapon::OnCollisionEnter(CCollider* pOtherCollider)
{

}
