#include "pch.h"
#include "CLevel.h"
#include "CObject.h"

CLevel::CLevel()
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

void CLevel::LevelRender(HDC _dc)
{
	for (size_t i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t ii = 0; ii < m_arrLayer[i].size(); ++ii)
		{
			m_arrLayer[i][ii]->ObjectRender(_dc);
		}
	}
}

