#include "pch.h"
#include "CTile.h"

#include "CTexture.h"
#include "CCameraMgr.h"
#include "CResourceMgr.h"

CTile::CTile()
	: m_pAtlas(nullptr)
	, m_iImgIdx(-1)
{
}

CTile::~CTile()
{
}

void CTile::SetImgIdx(int _imgidx)
{
	assert(m_pAtlas);

	int iCol = m_pAtlas->Width() / TILE_SIZE;
	int iRow = m_pAtlas->Height() / TILE_SIZE;

	int iImgMaxCount = iCol * iRow;
	// 이 iImgMsxCount 를 여기서 하는 이유가 뭘까? CreateTile 에서 해야 하는거 아닌가?

	assert(!(iImgMaxCount <= _imgidx));

	m_iImgIdx = _imgidx;
}

void CTile::AddImgIdx() 
{
	assert(m_pAtlas);

	int iCol = m_pAtlas->Width() / TILE_SIZE;
	int iRow = m_pAtlas->Height() / TILE_SIZE;
	int iImgMaxCount = iCol * iRow;

	++m_iImgIdx;

	// 최대 이미지 초과하는 경우, 다시 처음으로
	if (iImgMaxCount <= m_iImgIdx)
	{
		m_iImgIdx = 0;
	}

}

void CTile::ObjectTick()
{
}

void CTile::ObjectRender(HDC _dc)
{
	if (-1 == m_iImgIdx || nullptr == m_pAtlas)
	{
		return;
	}

	Vec vPos = CCameraMgr::GetInst()->GetRenderPos(GetPos());
	//Rectangle(_dc
	//	, (int)(vPos.x)
	//	, (int)(vPos.y)
	//	, (int)(vPos.x + TILE_SIZE)
	//	, (int)(vPos.y + TILE_SIZE));

	int iMaxCol = m_pAtlas->Width() / TILE_SIZE;

	int iCurRow = m_iImgIdx / iMaxCol;
	int iCurCol = m_iImgIdx % iMaxCol;

	BitBlt(_dc
		, (int)vPos.x
		, (int)vPos.y
		, TILE_SIZE, TILE_SIZE
		, m_pAtlas->GetDC()
		, iCurCol * TILE_SIZE
		, iCurRow * TILE_SIZE
		, SRCCOPY);
}

void CTile::TileSave(FILE* _pFile)
{
	// 위치
	Vec vPos = GetPos();
	fwrite(&vPos, sizeof(Vec), 1, _pFile);

	// 아틀라스 이미지 정보
	bool bAtlas = m_pAtlas;
	fwrite(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		// 키값 저장,
		wstring strKey = m_pAtlas->GetKey();
		SaveWString(strKey, _pFile);

		// 상대경로 저장
		wstring strRelativePath = m_pAtlas->GetRelativePath();
		SaveWString(strRelativePath, _pFile);
	}

	// 이미지 인덱스
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::TileLoad(FILE* _pFile)
{
	// 위치
	Vec vPos;
	fread(&vPos, sizeof(Vec), 1, _pFile);
	SetPos(vPos);

	// 아틀라스 이미지 정보
	bool bAtlas = false;
	fread(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		wstring strKey, strRelativePath;
		LoadWString(strKey, _pFile);
		LoadWString(strRelativePath, _pFile);
		m_pAtlas = CResourceMgr::GetInst()->LoadTexture(strKey, strRelativePath);

		// 이미지 인덱스
		fread(&m_iImgIdx, sizeof(int), 1, _pFile);
	}
}
