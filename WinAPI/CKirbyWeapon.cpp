#include "framework.h"
#include "CKirbyWeapon.h"
#include "CCollider.h"

CKirbyWeapon::CKirbyWeapon()
{
	m_vecScale = Vector(10, 10);
	m_layer = Layer::Weapon;
	m_strName = L"¹«±â";
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
