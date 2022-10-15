#include "pch.h"
#include "CLevelMgr.h"

#include "CStartLevel.h"
#include "CStage01Level.h"
#include "CEditorLevel.h"

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
	// Level 생성
	m_arrLevel[(UINT)LEVEL_TYPE::START] = new CStartLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CStage01Level;
	m_arrLevel[(UINT)LEVEL_TYPE::EDITOR] = new CEditorLevel;

	m_pCurLevel = m_arrLevel[(UINT)LEVEL_TYPE::EDITOR];
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

void CLevelMgr::ChangeLevel(LEVEL_TYPE _eNext)
{
	// 현재 레벨과 변경하려는 레벨이 동일한 경우
	assert(m_pCurLevel != m_arrLevel[(UINT)_eNext]);

	// 현재 레벨을 벗어남
	m_pCurLevel->LevelExit();

	m_pCurLevel = m_arrLevel[(UINT)_eNext];

	m_pCurLevel->LevelEnter();

}
