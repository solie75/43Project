#include "pch.h"
#include "CEditorLevel.h"
#include "CEngine.h"

#include "CTexture.h"
#include "CTile.h"
#include "CObject.h"

#include "CCameraMgr.h"
#include "CResourceMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"

CEditorLevel::CEditorLevel()
	:m_eMode(EDITOR_MODE::TILE)
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
	CreateTile(8, 6);

	// 각 타일에다가 사용할 아틀라스 이미지와, 이미지 인덱스를 세팅
	const vector<CObject*>& vecTile = GetLayer(LAYER::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->SetAtlas(pTex);
		((CTile*)vecTile[i])->SetImgIdx(0);
	}
}

void CEditorLevel::LevelTick()
{
	Update();
}

void CEditorLevel::LevelEnter()
{
	CLevel::LevelTick();
}

void CEditorLevel::LevelExit()
{
}

void CEditorLevel::Update()
{
	switch (m_eMode)
	{
	case EDITOR_MODE::TILE:
		Tile_Update();
		break;
	case EDITOR_MODE::ANIMATION:
		Animation_Update();
		break;
	case EDITOR_MODE::OBJECT:
		Object_Update();
		break;
	case EDITOR_MODE::NONE:
		return;
	}
}

void CEditorLevel::Tile_Update()
{
	if (IsTap(KEY::LBTN))
	{
		// 마우스 위치를 받아와서 실제 좌표로 변환
		Vec vMousePos = CCameraMgr::GetInst()->GetRealPos(MOUSE_POS);

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;
		// 이런 방식은 첫번째 파일이 realPos 기준으로 (0,0) 일대만 되는 것 아닌가

		if (0.f <= vMousePos.x && (UINT)iCol < GetTileXCount()
			&& 0.f <= vMousePos.y && (UINT)iRow < GetTileYCount())
		{
			int iIdx = iRow * GetTileXCount() + iCol;
			// iRow와 iCol 모두 0에서 부터 시작하기 때문에 iIdx 가 가능
			const vector<CObject*> vecTile = GetLayer(LAYER::TILE);
			((CTile*)vecTile[iIdx])->AddImgIdx();
		}
	}
	if (IsTap(KEY::_8))
	{
		SaveTile();
	}
	if (IsTap(KEY::_9))
	{
		LoadTile();
	}
}

void CEditorLevel::Animation_Update()
{
}

void CEditorLevel::Object_Update()
{
}

void CEditorLevel::SaveTile()
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"tile\\test.tile";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	// 타일 가로 세로 개수 저장
	UINT iTileXCount = GetTileXCount();
	UINT iTileYCount = GetTileYCount();

	fwrite(&iTileXCount, sizeof(UINT), 1, pFile);
	fwrite(&iTileYCount, sizeof(UINT), 1, pFile);

	// 각각의 타일 정보 저장
	const vector<CObject*>& vecTile = GetLayer(LAYER::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->TileSave(pFile);
	}

	fclose(pFile);
}

void CEditorLevel::LoadTile()
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"tile\\test.tile";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	// 타월 가로 세로 개수 읽기
	UINT iTileXCount = 0, iTileYCount = 0;
	
	fread(&iTileXCount, sizeof(UINT), 1, pFile);
	fread(&iTileYCount, sizeof(UINT), 1, pFile);

	// 읽은 개수에 맞게 다시 타일 배치
	CreateTile(iTileXCount, iTileYCount);

	// 배치한 각각의 타일의 데이터를 읽어온다
	const vector<CObject*>& vecTile = GetLayer(LAYER::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->TileLoad(pFile);
	}

	fclose(pFile);
}

// ======================
// Tile Count Dialog Proc
// ======================
INT_PTR CALLBACK TileCount(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}