#pragma once

class CLevel;

class CLevelMgr
{
	SINGLE(CLevelMgr);
private:
	CLevel* m_arrLevel[(UINT)LEVEL_TYPE::END];
	CLevel* m_pCurLevel;

public:
	void LevelMgrInit();
	void LevelMgrTick();
	void LevelMgrRender(HDC _dc);

	CLevel* GetCurLevel() { return m_pCurLevel; }
};

