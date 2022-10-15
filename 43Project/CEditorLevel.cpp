#include "pch.h"
#include "CEditorLevel.h"
#include "CEngine.h"

#include "CTexture.h"
#include "CTile.h"
#include "CObject.h"

#include "CCameraMgr.h"
#include "CResourceMgr.h"

CEditorLevel::CEditorLevel()
{
}

CEditorLevel::~CEditorLevel()
{
}

void CEditorLevel::LevelInit()
{
	// 카메사 시점
	Vec vResolution = CEngine::GetInst()->GetResolution();
	CCameraMgr::GetInst()->SetLook(vResolution / 2.f);

	// 타일이 사용할 아틀라스 이미지 로딩
	CTexture* pTex = CResourceMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\TILE.bmp");

	// 타일 생성
	CreateTile(8, 8);

	// 각 타일에다가 사용할 아틀라스 이미지와, 이미지 인덱스를 세팅
	const vector<CObject*>& vecTile = GetLayer(LAYER::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->SetAtlas(pTex);
		((CTile*)vecTile[i])->SetImgIdx((int)i);
	}
}

void CEditorLevel::LevelTick()
{
}

void CEditorLevel::LevelEnter()
{
	CLevel::LevelTick();
}

void CEditorLevel::LevelExit()
{
}