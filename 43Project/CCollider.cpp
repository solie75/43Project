#include "pch.h"
#include "CCollider.h"
#include "CEngine.h"

#include "CObject.h"

#include "CCameraMgr.h"



CCollider::CCollider(CObject* _pOwner)
	: CComponent(_pOwner)
	, m_iOverlapCount(0)
{
}

CCollider::~CCollider()
{
}

void CCollider::ComponentTick()
{
	// 충돌체의 최종 위치값을 결정한다.
	m_vFinalPos = GetOwner()->GetPos() + m_vOffsetPos;

	// 중첩수가 음수인 경우
	assert(!(m_iOverlapCount < 0));
}

void CCollider::ComponentRender(HDC _dc)
{
	// 충돌체를 그린다.
	// 필요한 펜과 브러시를 만든다( 또는 가져온다. )
	HPEN hPen = nullptr;

	if (0 < m_iOverlapCount)
	{
		hPen = CEngine::GetInst()->GetPen(PEN_TYPE::RED);
	}
	else
	{
		hPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);
	}
	//HPEN hGreenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	
	// 펜과 브러쉬 가져오는 코드
	// HPEN hGreenPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);

	HBRUSH hNULLBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	// DC 의 기존 펜과 브러시를 새로 가져온 것으로 대체
	HPEN hOriginPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNULLBrush);

	Vec vRenderPos = CCameraMgr::GetInst()->GetRenderPos(m_vFinalPos);

	// 사각형 그리기
	Rectangle(_dc
		, (int)(vRenderPos.x - m_vScale.x / 2.f)
		, (int)(vRenderPos.y - m_vScale.y / 2.f)
		, (int)(vRenderPos.x + m_vScale.x / 2.f)
		, (int)(vRenderPos.y + m_vScale.y / 2.f));

	// DC 의 GDI 오브젝트를 기존의 펜과 브러시로 되돌린다.
	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);

	// 사용한 펜을 삭제한다. 브러시는 얻어 쓴것이기 때문에 사제하지 않는다.
	//DeleteObject(hGreenPen);
}

void CCollider::BeginOverlap(CCollider* _other)
{
	++m_iOverlapCount;
	GetOwner()->CollisionBegin(_other);
}

void CCollider::OnOverlap(CCollider* _other)
{
	GetOwner()->Colliding(_other);
}

void CCollider::EndOverlap(CCollider* _other)
{
	--m_iOverlapCount;
	GetOwner()->CollisionEnd(_other);
}