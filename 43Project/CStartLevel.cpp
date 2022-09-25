#include "pch.h"
#include "CStartLevel.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

CStartLevel::CStartLevel()
{
}

CStartLevel::~CStartLevel()
{
}

void CStartLevel::LevelInit()
{
	// Object 持失
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec(500.f, 500.f));
	pObj->SetScale(Vec(100.f, 100.f));
	AddObject(pObj, LAYER::PLAYER);

	// Monster 持失
	pObj = new CMonster;
	pObj->SetPos(Vec(960.f, 200.f));
	pObj->SetScale(Vec(150.f, 150.f));
	AddObject(pObj, LAYER::MONSTER);
}

