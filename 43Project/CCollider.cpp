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
	// �浹ü�� ���� ��ġ���� �����Ѵ�.
	m_vFinalPos = GetOwner()->GetPos() + m_vOffsetPos;
}

void CCollider::ComponentRender(HDC _dc)
{
	// �浹ü�� �׸���.
	// �ʿ��� ��� �귯�ø� �����( �Ǵ� �����´�. )
	HPEN hGreenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	// ��� �귯�� �������� �ڵ�
	// HPEN hGreenPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);
	HBRUSH hNULLBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	// DC �� ���� ��� �귯�ø� ���� ������ ������ ��ü
	HPEN hOriginPen = (HPEN)SelectObject(_dc, hGreenPen);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNULLBrush);

	// �簢�� �׸���
	Rectangle(_dc
		, (int)(m_vFinalPos.x - m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y - m_vScale.y / 2.f)
		, (int)(m_vFinalPos.x + m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y + m_vScale.y / 2.f));

	// DC �� GDI ������Ʈ�� ������ ��� �귯�÷� �ǵ�����.
	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);

	// ����� ���� �����Ѵ�. �귯�ô� ��� �����̱� ������ �������� �ʴ´�.
	DeleteObject(hGreenPen);
}