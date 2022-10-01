#include "pch.h"
#include "CPlayer.h"
#include "CMissile.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CEventMgr.h"

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
		// 현재 레벨에 생성한 미사일을 추가
		//CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel(); // CEventMgr에서 관리 

		// 미사일 생성
		for (int i = 0; i < 3; ++i)
		{
			CMissile* pMissile = new CMissile;
			pMissile->SetPos(GetPos());
			pMissile->SetScale(Vec(20.f, 20.f));
			pMissile->SetSpeed(400.f);
			pMissile->SetDir(75.f + 15.f * (float)i); // 75도 90도 105도 세갈래로 미사일 발사
			//pCurLevel->AddObject(pMissile, LAYER::PLAYER_PROJECTILE);

			tEvent even ={};
			even.eType = EVENT_TYPE::CREATE_OBJECT;
			even.wPARAM = (DWORD_PTR)pMissile;
			even.lPARAM = (DWORD_PTR)LAYER::PLAYER_PROJECTILE;

			CEventMgr::GetInst()->AddEvent(even);
		}
	}
	SetPos(vPos);

	// 여기에서 상위 객체 클래스의 Tick  재호출 Collider 를 위해서
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


	// 부모 오브젝트의 Render 도 실행( Component Render 흐름)
	CObject::ObjectRender(_dc);
}

void CPlayer::CollisionBegin(CCollider* _pOther)
{
	int a = 0;
}

void CPlayer::Colliding(CCollider* _pOther)
{
	int a = 0;
}

void CPlayer::CollisionEnd(CCollider* _pOther)
{
	int a = 0;
}
