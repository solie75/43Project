#include "pch.h"
#include "CLevel.h"
#include "CObject.h"

CLevel::CLevel()
{
}

CLevel::~CLevel()
{
	// 모든 오브젝트 삭제
	for (size_t i = 0; i < m_vecObject.size(); ++i)
	{
		DEL(m_vecObject[i]);
	}
}

void CLevel::LevelTick()
{
	for (size_t i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->ObjectTick();
	}
}

void CLevel::LevelRender(HDC _dc)
{
	for (size_t i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->ObjectRender(_dc);
	}
}

