#include "pch.h"
#include "CPlayer.h"
#include "CMissile.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CLevelMgr.h"

#include "CLevel.h"

CPlayer::CPlayer()
	: m_fSpeed(100.f)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::ObjectTick()
{
	Vec vPos = GetPos();

	if (IsPressed(KEY::LEFT))
	{
		vPos.x -= m_fSpeed * DT;
	}

	if (IsPressed(KEY::RIGHT))
	{
		vPos.x += m_fSpeed * DT;
	}

	if (IsPressed(KEY::UP))
	{
		vPos.y -= m_fSpeed * DT;
	}

	if (IsPressed(KEY::DOWN))
	{
		vPos.y += m_fSpeed * DT;
	}

	if (IsTap(KEY::SPACE))
	{
		// ���� ������ ������ �̻����� �߰�
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

		// �̻��� ����
		for (int i = 0; i < 3; ++i)
		{
			CMissile* pMissile = new CMissile;
			pMissile->SetPos(GetPos());
			pMissile->SetScale(Vec(20.f, 20.f));
			pMissile->SetSpeed(400.f);
			pMissile->SetDir(75.f + 15.f * (float)i); // 75�� 90�� 105�� �������� �̻��� �߻�
			pCurLevel->AddObject(pMissile);
		}
	}
	SetPos(vPos);
}

void CPlayer::ObjectRender(HDC _dc)
{
	CObject::ObjectRender(_dc);
}

