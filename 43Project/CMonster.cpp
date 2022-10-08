#include "pch.h"
#include "CMonster.h"
#include "CPlayer.h"
#include "CTexture.h"
#include "CResourceMgr.h"
#include "CCollider.h"

#include "CTimeMgr.h"
#include "CCameraMgr.h"


CMonster::CMonster()
	: m_iHP(3)
	, m_pTarget(nullptr)
	, m_pTexture(nullptr)
{
	CreateCollider();
	// where is OffSet Setting..?
	GetCollider()->SetScale(Vec(100.f, 100.f));

	//m_pTexture = CResourceMgr::GetInst()->LoadTexture(L"Plane", L"animation\\Fighter.bmp"); // load  의 과정은 이미 startlevel 에서 진행 했음
	m_pTexture = CResourceMgr::GetInst()->FindTexture(L"FighterPlane");
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
	}*/ // 추적기능 주석처리

	CObject::ObjectTick();
}

void CMonster::ObjectRender(HDC _dc)
{
	Vec vPos = CCameraMgr::GetInst()->GetRenderPos(GetPos());
	Vec vSize = GetScale();

	//HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	//HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	static float fRatio = 0.f;
	static float Dir = 1.f;
	fRatio += DT * Dir * 8.f ;

	if (1.f < fRatio)
	{
		fRatio = 1.f;
		Dir = -1.f;
	}
	else if (fRatio < 0.f)
	{
		fRatio = 0.f;
		Dir = 1;
	}

	BLENDFUNCTION tBlend = {};

	tBlend.AlphaFormat = AC_SRC_ALPHA;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255.f * fRatio);

	AlphaBlend(_dc
		, (int)(vPos.x - m_pTexture->Width() / 2.f)
		, (int)(vPos.y - m_pTexture->Height() / 2.f)
		, m_pTexture->Width()
		, m_pTexture->Height()
		, m_pTexture->GetDC()
		, 0, 0
		, m_pTexture->Width()
		, m_pTexture->Height()
		, tBlend);

	//Rectangle(_dc, (int)(vPos.x - vSize.x / 2.f)
	//	, (int)(vPos.y - vSize.y / 2.f)
	//	, (int)(vPos.x + vSize.x / 2.f)
	//	, (int)(vPos.y + vSize.y / 2.f));

	//SelectObject(_dc, hOriginBrush);

	CObject::ObjectRender(_dc);
}

void CMonster::CollisionBegin(CCollider* _pOther)
{
	SetDead();
}
