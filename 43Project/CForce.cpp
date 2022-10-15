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

void CForce::ObjectTick()
{
	m_fAccTime += DT;

	if (m_fDuration < m_fAccTime)
	{
		SetDead();
		return;
	}

	// Player layer �� ����
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	const vector<CObject*>& vecPlayerLayer = pCurLevel->GetLayer(LAYER::PLAYER);

	for (size_t i = 0; i < vecPlayerLayer.size(); ++i)
	{
		if (nullptr == vecPlayerLayer[i]->GetRigidBody())
		{
			continue;
		}

		// Force ���� Player�� ���ϴ� ����
		Vec vForceDir = vecPlayerLayer[i]->GetPos() - GetPos();

		// Force �� Player������ �Ÿ�
		float fDistance = vForceDir.ShiftingDistance();

		//float fRatio = 1.f - (fDistance / m_fRadius)
		//Saturate(fRatio); // 0 ���� 1 ���� ���� .../
		float fRatio = cosf((fDistance / m_fForceRadius) * PI * 0.5f);
		// ���� �Ÿ��� �ݰ��� ������ �ݰ濡 ���Ͽ� �Ÿ��� ���ۼ�Ʈ������ ���� ������ ���´� ���� ��� �ݰ��� 100�̰� �Ÿ��� 70�̸� ������ 70�ΰ��̴�.
		 //��ü�� ������ �Ÿ��� �ݰ��� ����ΰ�.
		Saturate(fRatio);
		// ���� ��ü�� �÷��̾� ��ü ������ �Ÿ��� �� ��ü�� �ݰ� �� ������ 0�̻� 1���Ͽ��� �Ѵ�.
		// 1�� �ʰ� �Ѵٸ� ���� -�� �Ǿ ������ ���Ƶ��̴� ���� �Ǳ� �����̴�.

		//Force ���� �÷��̾�� �� ���� ũ��
		vForceDir.Normalize();
		vForceDir *= m_fForceScale * fRatio;
		// ����ü�� ������ �ִ� ���� ������ ���ؼ� �� ��ü�� �÷��̾� ��ü�� �Ÿ��� �ָ� ���� �� �ް� ������ ���� ������ �ްԲ� ���־�� �Ѵ�.

		vecPlayerLayer[i]->GetRigidBody()->AddForce(vForceDir);
	}

}

void CForce::ObjectRender(HDC _dc)
{
	HPEN hGreenPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);
	HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	//dC �� ���� ��� �귯�ø� ���� ������ ������ ��ü
	HPEN hOriginPen = (HPEN)SelectObject(_dc, hGreenPen);
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	Vec vPos = CCameraMgr::GetInst()->GetRenderPos(GetPos());

	Ellipse(_dc,
		(int)(vPos.x - m_fForceRadius),
		(int)(vPos.y - m_fForceRadius),
		(int)(vPos.x + m_fForceRadius),
		(int)(vPos.y + m_fForceRadius));

	// DC�� GDI ������Ʈ ���� ������ ��� �귯���� �ǵ�����.
	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hPrevBrush);
		
}

