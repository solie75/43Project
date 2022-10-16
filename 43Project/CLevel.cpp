#include "pch.h"
#include "CLevel.h"
#include "CObject.h"
#include "CTile.h"

CLevel::CLevel()
	: m_iTileXCount(0)
	, m_iTileYCount(0)
{
}

CLevel::~CLevel()
{
	// 모든 오브젝트 삭제
	for (size_t i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t ii = 0; ii < m_arrLayer[i].size(); ++ii)
		{
			DEL(m_arrLayer[i][ii]);
		}
	}
}

void CLevel::LevelTick()
{
	for (size_t i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t ii = 0; ii < m_arrLayer[i].size(); ++ii)
		{
			m_arrLayer[i][ii]->ObjectTick();
		}
	}
}

void CLevel::Final_Tick()
{
	for (size_t i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t ii = 0; ii < m_arrLayer[i].size(); ++ii)
		{
			m_arrLayer[i][ii]->Final_Tick();
		}
	}
}

void CLevel::LevelRender(HDC _dc)
{
	/*for (size_t i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t ii = 0; ii < m_arrLayer[i].size(); ++ii)
		{
			m_arrLayer[i][ii]->ObjectRender(_dc);
		}
	}*/
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		vector<CObject*>::iterator iter = m_arrLayer[i].begin();

		for (; iter != m_arrLayer[i].end();)
		{
			if ((*iter)->IsDead())
			{
				iter = m_arrLayer[i].erase(iter);
			}
			else
			{
				(*iter)->ObjectRender(_dc);
				++iter;
			}
		}
	}
}

void CLevel::DeleteAllObject()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			if (m_arrLayer[i][j]->IsDead())
			{
				continue;
			}

			DEL(m_arrLayer[i][j]);
		}

		// 동적할당 해지시킨 주소값들을 벡터 내에서 비우기
		m_arrLayer[i].clear();
	}
}

void CLevel::DeleteObject(LAYER _eLayer)
// 특정 레이어의 모든 객체를 삭제한다.
{
	for (size_t i = 0; i < m_arrLayer[(UINT)_eLayer].size(); ++i)
	{
		delete m_arrLayer[(UINT)_eLayer][i];
	}
	m_arrLayer[(UINT)_eLayer].clear();
}

void CLevel::CreateTile(UINT _X, UINT _Y)
{
	// 기존에 깔아 둔 타일 제거
	DeleteObject(LAYER::TILE);

	m_iTileXCount = _X;
	m_iTileYCount = _Y;

	// 지정된 가로 세로 숫자에 맞추어 타일 배치
	for (UINT iRow = 0; iRow < m_iTileYCount; ++iRow)
	{
		for (UINT iCol = 0; iCol < m_iTileXCount; ++iCol)
		{
			CTile* pTile = new CTile;
			pTile->SetPos(Vec((float)(TILE_SIZE * iCol), (float)(TILE_SIZE * iRow)));
			AddObject(pTile, LAYER::TILE);
		}
	}
}
