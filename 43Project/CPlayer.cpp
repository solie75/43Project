#include "pch.h"
#include "CPlayer.h"
#include "CMissile.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CLevelMgr.h"

#include "CLevel.h"

#include "CCollider.h"

CPlayer::CPlayer()
	: m_fSpeed(100.f)
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec(0.f, 0.f));
	GetCollider()->SetScale(Vec(80.f, 80.f));
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
			pCurLevel->AddObject(pMissile, LAYER::MONSTER_PROJECTILE);
		}
	}
	SetPos(vPos);

	// ���⿡�� ���� ��ü Ŭ������ Tick  ��ȣ�� Collider �� ���ؼ�
	CObject::ObjectTick();
}

void CPlayer::ObjectRender(HDC _dc)
{
	Vec vPos = CObject::GetPos();
	Vec vScale = CObject::GetScale();

	Rectangle(_dc,
		(int)(vPos.x - vScale.x / 2.f),
		(int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f),
		(int)(vPos.y + vScale.y / 2.f)
	);


	// �θ� ������Ʈ�� Render �� ����( Component Render �帧)
	CObject::ObjectRender(_dc);
}

