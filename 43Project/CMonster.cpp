#include "pch.h"
#include "CMonster.h"

#include "CCollider.h"

CMonster::CMonster()
{
	CreateCollider();
	// where is OffSet Setting..?
	GetCollider()->SetScale(Vec(100.f, 100.f));
}

CMonster::~CMonster()
{
}

void CMonster::ObjectTick()
{
	CObject::ObjectTick();
}

void CMonster::ObjectRender(HDC _dc)
{
	Vec vPos = GetPos();
	Vec vSize = GetScale();

	Rectangle(_dc, (int)(vPos.x - vSize.x / 2.f)
		, (int)(vPos.y - vSize.y / 2.f)
		, (int)(vPos.x + vSize.x / 2.f)
		, (int)(vPos.y + vSize.y / 2.f));

	CObject::ObjectRender(_dc);
}

