#include "pch.h"
#include "CTile.h"

#include "CTexture.h"
#include "CCameraMgr.h"

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
	// �� iImgMsxCount �� ���⼭ �ϴ� ������ ����? CreateTile ���� �ؾ� �ϴ°� �ƴѰ�?

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

	// �ִ� �̹��� �ʰ��ϴ� ���, �ٽ� ó������
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

void CTile::TileSave(FILE* _pFIle)
{
}

void CTile::TileLoad(FILE* _pFile)
{
}


