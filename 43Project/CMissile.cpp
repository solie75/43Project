#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"

CMissile::CMissile()
	: m_fSpeed(200.f)
	, m_fDegree(80.f)
{
}

CMissile::~CMissile()
{
}

void CMissile::ObjectTick()
{
	Vec vPos = GetPos();

	float fRadian = (m_fDegree * PI) / 180.f;
	vPos.x += m_fSpeed * cosf(fRadian) * DT;
	vPos.y -= m_fSpeed * sinf(fRadian) * DT;

	SetPos(vPos);
}

void CMissile::ObjectRender(HDC _dc)
{
	Vec vPos = GetPos();
	Vec vSize = GetScale();

	Ellipse(_dc, (int)(vPos.x - vSize.x / 2.f)
		, (int)(vPos.y - vSize.y / 2.f)
		, (int)(vPos.x + vSize.x / 2.f)
		, (int)(vPos.y + vSize.y / 2.f));
}

