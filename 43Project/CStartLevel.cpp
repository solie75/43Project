#include "pch.h"
#include "CStartLevel.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CCollisionMgr.h"

CStartLevel::CStartLevel()
{
}

CStartLevel::~CStartLevel()
{
}

void CStartLevel::LevelInit()
{
	// Object 积己
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec(500.f, 500.f));
	pObj->SetScale(Vec(100.f, 100.f));
	AddObject(pObj, LAYER::PLAYER);

	// Monster 积己
	CMonster* pMonster = new CMonster;
	pMonster->SetPos(Vec(960.f, 200.f));
	pMonster->SetScale(Vec(150.f, 150.f));
	pMonster->SetTarget((CPlayer*)pObj);
	AddObject(pMonster, LAYER::MONSTER);

	/*pObj = new CMonster;
	pObj->SetPos(Vec(200.f, 200.f));
	pObj->SetScale(Vec(150.f, 150.f));
	AddObject(pObj, LAYER::MONSTER);*/

	// Level 狼 面倒 汲沥
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER_PROJECTILE, LAYER::MONSTER);
}

