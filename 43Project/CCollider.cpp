#include "pch.h"
#include "CCollider.h"
#include "CEngine.h"

#include "CObject.h"



CCollider::CCollider(CObject* _pOwner)
	: CComponent(_pOwner)
{
}

CCollider::~CCollider()
{
}

void CCollider::ComponentTick()
{
	// 충돌체의 최종 위치값을 결정한다.
	m_vFinalPos = GetOwner()->GetPos() + m_vOffsetPos;
}

void CCollider::ComponentRender(HDC _dc)
{
	// 충돌체를 그린다.
	// 필요한 펜과 브러시를 만든다( 또는 가져온다. )
	HPEN hGreenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	// 펜과 브러쉬 가져오는 코드
	// HPEN hGreenPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);
	HBRUSH hNULLBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	// DC 의 기존 펜과 브러시를 새로 가져온 것으로 대체
	HPEN hOriginPen = (HPEN)SelectObject(_dc, hGreenPen);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNULLBrush);

	// 사각형 그리기
}