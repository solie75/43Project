#include "pch.h"
#include "CLevelMgr.h"

#include "CStartLevel.h"
#include "CStage01Level.h"

CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_pCurLevel(nullptr)
{}

CLevelMgr::~CLevelMgr()
{
	for (size_t i = 0; i < (int)LEVEL_TYPE::END; ++i)
	{
		DEL(m_arrLevel[i]);
	}
}

void CLevelMgr::LevelMgrInit()
{
	// Level »ý¼º
	m_arrLevel[(UINT)LEVEL_TYPE::START] = new CStartLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CStage01Level;

	m_pCurLevel = m_arrLevel[(UINT)LEVEL_TYPE::START];
	m_pCurLevel->LevelInit();
}

void CLevelMgr::LevelMgrTick()
{
	m_pCurLevel->LevelTick();
	m_pCurLevel->Final_Tick();
}

void CLevelMgr::LevelMgrRender(HDC _dc)
{
	m_pCurLevel->LevelRender(_dc);
}
