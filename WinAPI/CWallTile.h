#pragma once
#include "CTile.h"

enum class CollisionDir
{
	Down,
	Up,
	Left,
	Right,
	None,

	Size,
};

struct ColliderInfo
{
	Vector pos;
	Vector scale;

	float left;
	float right;
	float up;
	float down;

	ColliderInfo(Vector pos, Vector scale)
	{
		this->pos = pos;
		this->scale = scale;

		left = pos.x - scale.x * 0.5f;
		right = pos.x + scale.x * 0.5f;
		up = pos.y - scale.y * 0.5f;
		down = pos.y + scale.y * 0.5f;
	}
};

class CWallTile : public CTile
{
public:
	CWallTile();
	virtual ~CWallTile();

private:
	CollisionDir	m_colDir;
	float			m_offSet;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	void OnCollisionEnter(CCollider* pOther) override;
	void OnCollisionStay(CCollider* pOther) override;
	void OnCollisionExit(CCollider* pOther) override;

private:
	CollisionDir GetCollisionDir(CCollider* pOther);
};

