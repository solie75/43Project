#include "pch.h"
#include "CForce.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CCameraMgr.h"

#include "CLevel.h"
#include "cRigidBody.h"


CForce::CForce()
	: m_fAccTime(0.f)
	, m_fDuration(0.f)
	, m_fForceScale(0.f)
	, m_fForceRadius(0.f)
{
}

CForce::~CForce()
{
}

void CForce::CForceTick()
{
	m_fAccTime += DT;

	if (m_fDuration < m_fAccTime)
	{
		SetDead();
		return;
	}

	// Player layer 에 접근
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	const vector<CObject*>& vecPlayerLayer = pCurLevel->GetLayer(LAYER::PLAYER);

	for (size_t i = 0; i < vecPlayerLayer.size(); ++i)
	{
		if (nullptr == vecPlayerLayer[i]->GetRigidBody())
		{
			continue;
		}

		// Force 에서 Player를 향하는 벡터
		Vec vForceDir = vecPlayerLayer[i]->GetPos() - GetPos();

		// Force 와 Player사이의 거리
		//float fDistance = vForceDir.ShiftingDistance();

		//float fRatio = 1.f - (fDistance / m_fRadius)
		//Saturate(fRatio); // 0 에서 1 사이 보정 .../
		//float fRatio = cosf((fDistance / m_fForceRadius) * PI * 0.5f);
		// 객체와 힘과의 거리는 반경의 몇배인가.
		//Saturate(fRatio);
		// 강의 참고

		//Force 에서 플레이어에게 줄 힘의 크기
		vForceDir.Normalize();
		//vForceDir *= m_fForceScale * fRatio;


		vForceDir *= m_fForceScale;

		vecPlayerLayer[i]->GetRigidBody()->AddForce(vForceDir);
	}

}

void CForce::CForceRender(HDC _dc)
{
	HPEN hGreenPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);
	HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	//dC 의 기존 펜과 브러시를 새로 가져온 것으로 대체
	HPEN hOriginPen = (HPEN)SelectObject(_dc, hGreenPen);
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	Vec vPos = CCameraMgr::GetInst()->GetRenderPos(GetPos());

	Ellipse(_dc,
		(int)(vPos.x - m_fForceRadius),
		(int)(vPos.y - m_fForceRadius),
		(int)(vPos.x + m_fForceRadius),
		(int)(vPos.y + m_fForceRadius));

	// DC의 GDI 오브젝트 들을 기존의 펜과 브러쉬로 되돌린다.
	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hPrevBrush);
		
}

