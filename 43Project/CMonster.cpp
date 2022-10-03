#include "pch.h"
#include "CMonster.h"
#include "CPlayer.h"

#include "CCollider.h"

#include "CTimeMgr.h"
#include "CCameraMgr.h"


CMonster::CMonster()
	: m_iHP(3)
	, m_pTarget(nullptr)
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
	/*if (IsValid(m_pTarget))
	{
		Vec vTargetPos = m_pTarget->GetPos();
		m_pTarget->SetName(L"Player");
		Vec vPos = GetPos();

		Vec vDir = vTargetPos - vPos;
		vDir.Normalize();

		vPos.x += vDir.x * 100.f * DT;
		vPos.y += vDir.y * 100.f * DT;

		SetPos(vPos);
	}*/ // 眠利扁瓷 林籍贸府

	CObject::ObjectTick();
}

void CMonster::ObjectRender(HDC _dc)
{
	Vec vPos = CCameraMgr::GetInst()->GetRenderPos(GetPos());
	Vec vSize = GetScale();

	HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	Rectangle(_dc, (int)(vPos.x - vSize.x / 2.f)
		, (int)(vPos.y - vSize.y / 2.f)
		, (int)(vPos.x + vSize.x / 2.f)
		, (int)(vPos.y + vSize.y / 2.f));

	SelectObject(_dc, hOriginBrush);

	CObject::ObjectRender(_dc);
}

void CMonster::CollisionBegin(CCollider* _pOther)
{
	SetDead();
}
