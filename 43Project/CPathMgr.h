#pragma once


class CPathMgr
{
	SINGLE(CPathMgr)
private:
	wchar_t m_szContentPath[245];

public:
	void PathMgrTick();
	void PathMgrRender();

public:
	const wchar_t* GetContentPath() { return m_szContentPath; }
};

