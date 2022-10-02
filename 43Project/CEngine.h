#pragma once

class CEngine
{
	SINGLE(CEngine)

private:
	HWND m_hMainWnd;
	HDC m_hDC;

	HDC m_hMemDC;
	HBITMAP m_hMemBit;

	POINT m_ptResolution;

	HPEN m_arrPen[(UINT)PEN_TYPE::END];

public:
	HWND GetMainWnd() { return m_hMainWnd; }
	HPEN GetPen(PEN_TYPE _type) { return m_arrPen[(UINT)_type]; }
	HDC GetMainDC() { return m_hMemDC; }
	POINT GetResolution() { return m_ptResolution; }

public:
	void CEngineInit(HWND _hWnd, UINT _iWidth, UINT _iHeight);
	void progress();

private:
	void CEngineTick();
	void CEngineRender();
	void CreatePenBrush();
};

