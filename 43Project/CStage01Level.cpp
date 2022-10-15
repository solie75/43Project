#include "pch.h"
#include "CStage01Level.h"

#include "CCameraMgr.h"
#include "CKeyMgr.h"

#include "CPlayer.h"

CStage01Level::CStage01Level()
{
}

CStage01Level::~CStage01Level()
{
}

void CStage01Level::LevelInit()
{
	// Create Player
	CObject* pPlayer = new CPlayer;
	pPlayer->SetPos(Vec(500.f, 100.f));
	pPlayer->SetScale(Vec(100.f, 100.f));
	AddObject(pPlayer, LAYER::PLAYER);

	//Vec vPos = CCameraMgr::GetInst()->GetRealPos(pPlayer->GetPos());

	//Instantiate(pPlayer, vPos, LAYER::GROUNDPLATFORM);
}

void CStage01Level::LevelTick()
{
	CLevel::LevelTick();

	if (IsTap(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::START);
	}
}

void CStage01Level::LevelEnter()
{
	LevelInit();
}

void CStage01Level::LevelExit()
{
	DeleteAllObject();
}

