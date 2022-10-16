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