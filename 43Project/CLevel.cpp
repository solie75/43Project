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
	// ��� ������Ʈ ����
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

		// �����Ҵ� ������Ų �ּҰ����� ���� ������ ����
		m_arrLayer[i].clear();
	}
}

void CLevel::DeleteObject(LAYER _eLayer)
// Ư�� ���̾��� ��� ��ü�� �����Ѵ�.
{
	for (size_t i = 0; i < m_arrLayer[(UINT)_eLayer].size(); ++i)
	{
		delete m_arrLayer[(UINT)_eLayer][i];
	}
	m_arrLayer[(UINT)_eLayer].clear();
}

void CLevel::CreateTile(UINT _X, UINT _Y)
{
	// ������ ��� �� Ÿ�� ����
	DeleteObject(LAYER::TILE);

	m_iTileXCount = _X;
	m_iTileYCount = _Y;

	// ������ ���� ���� ���ڿ� ���߾� Ÿ�� ��ġ
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
