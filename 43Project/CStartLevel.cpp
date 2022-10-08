#include "pch.h"
#include "CStartLevel.h"

#include "CEngine.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CCameraMgr.h"
#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"

CStartLevel::CStartLevel()
{
}

CStartLevel::~CStartLevel()
{
}

void CStartLevel::LevelInit()
{
	// Textrue 로딩
	CResourceMgr::GetInst()->LoadTexture(L"FighterPlane", L"texture\\FighterPlane.bmp");

	// Object 생성
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec(500.f, 500.f));
	pObj->SetScale(Vec(100.f, 100.f));
	AddObject(pObj, LAYER::PLAYER);

	// Monster 생성
	CMonster* pMonster = new CMonster;
	pMonster->SetPos(Vec(960.f, 200.f));
	pMonster->SetScale(Vec(150.f, 150.f));
	pMonster->SetTarget((CPlayer*)pObj);
	AddObject(pMonster, LAYER::MONSTER);

	/*pObj = new CMonster;
	pObj->SetPos(Vec(200.f, 200.f));
	pObj->SetScale(Vec(150.f, 150.f));
	AddObject(pObj, LAYER::MONSTER);*/

	// Level 의 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER_PROJECTILE, LAYER::MONSTER);
	
	Vec vResolution = CEngine::GetInst()->GetResolution();
	CCameraMgr::GetInst()->SetLook(vResolution / 2.f);
}

void CStartLevel::LevelTick()
{
	CLevel::LevelTick();

	if (IsTap(KEY::ENTER))
	{
		CCameraMgr::GetInst()->FadeOut(1.f);
		CCameraMgr::GetInst()->FadeIn(1.f);
	}
}

