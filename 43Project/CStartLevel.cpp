#include "pch.h"
#include "CStartLevel.h"

#include "CObject.h"
#include "CPlayer.h"

CStartLevel::CStartLevel()
{
}

CStartLevel::~CStartLevel()
{
}

void CStartLevel::LevelInit()
{
	// Object »ý¼º
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec(500.f, 500.f));
	pObj->SetScale(Vec(100.f, 100.f));
	AddObject(pObj);
}

