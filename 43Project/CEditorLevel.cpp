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
	// ī�޻� ����
	Vec vResolution = CEngine::GetInst()->GetResolution();
	CCameraMgr::GetInst()->SetLook(vResolution / 2.f);

	// Ÿ���� ����� ��Ʋ�� �̹��� �ε�
	CTexture* pTex = CResourceMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\TILE.bmp");

	// Ÿ�� ����
	CreateTile(8, 6);

	// �� Ÿ�Ͽ��ٰ� ����� ��Ʋ�� �̹�����, �̹��� �ε����� ����
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
		// ���콺 ��ġ�� �޾ƿͼ� ���� ��ǥ�� ��ȯ
		Vec vMousePos = CCameraMgr::GetInst()->GetRealPos(MOUSE_POS);

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;
		// �̷� ����� ù��° ������ realPos �������� (0,0) �ϴ븸 �Ǵ� �� �ƴѰ�

		if (0.f <= vMousePos.x && (UINT)iCol < GetTileXCount()
			&& 0.f <= vMousePos.y && (UINT)iRow < GetTileYCount())
		{
			int iIdx = iRow * GetTileXCount() + iCol;
			// iRow�� iCol ��� 0���� ���� �����ϱ� ������ iIdx �� ����
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

	// Ÿ�� ���� ���� ���� ����
	UINT iTileXCount = GetTileXCount();
	UINT iTileYCount = GetTileYCount();

	fwrite(&iTileXCount, sizeof(UINT), 1, pFile);
	fwrite(&iTileYCount, sizeof(UINT), 1, pFile);

	// ������ Ÿ�� ���� ����
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

	// Ÿ�� ���� ���� ���� �б�
	UINT iTileXCount = 0, iTileYCount = 0;
	
	fread(&iTileXCount, sizeof(UINT), 1, pFile);
	fread(&iTileYCount, sizeof(UINT), 1, pFile);

	// ���� ������ �°� �ٽ� Ÿ�� ��ġ
	CreateTile(iTileXCount, iTileYCount);

	// ��ġ�� ������ Ÿ���� �����͸� �о�´�
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