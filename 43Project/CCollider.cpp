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
	// �浹ü�� ���� ��ġ���� �����Ѵ�.
	m_vFinalPos = GetOwner()->GetPos() + m_vOffsetPos;

	// ��ø���� ������ ���
	assert(!(m_iOverlapCount < 0));
}

void CCollider::ComponentRender(HDC _dc)
{
	// �浹ü�� �׸���.
	// �ʿ��� ��� �귯�ø� �����( �Ǵ� �����´�. )
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
	
	// ��� �귯�� �������� �ڵ�
	// HPEN hGreenPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);

	HBRUSH hNULLBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	// DC �� ���� ��� �귯�ø� ���� ������ ������ ��ü
	HPEN hOriginPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNULLBrush);

	Vec vRenderPos = CCameraMgr::GetInst()->GetRenderPos(m_vFinalPos);

	// �簢�� �׸���
	Rectangle(_dc
		, (int)(vRenderPos.x - m_vScale.x / 2.f)
		, (int)(vRenderPos.y - m_vScale.y / 2.f)
		, (int)(vRenderPos.x + m_vScale.x / 2.f)
		, (int)(vRenderPos.y + m_vScale.y / 2.f));

	// DC �� GDI ������Ʈ�� ������ ��� �귯�÷� �ǵ�����.
	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);

	// ����� ���� �����Ѵ�. �귯�ô� ��� �����̱� ������ �������� �ʴ´�.
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