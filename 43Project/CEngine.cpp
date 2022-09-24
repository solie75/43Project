#include "pch.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"


CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_hDC(nullptr)
{

}

CEngine::~CEngine()
{
	ReleaseDC(m_hMainWnd, m_hDC);
	DeleteDC(m_hMemDC);
	DeleteObject(m_hMemBit);
}

void CEngine::CEngineInit(HWND _hWnd, UINT _iWidth, UINT _iHeight)
{
	m_hMainWnd = _hWnd;
	m_ptResolution.x = _iWidth;
	m_ptResolution.y = _iHeight;

	// 윈도우 크기 설정
	RECT rt = { 0, 0, (LONG)_iWidth, (LONG)_iHeight };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// HDC 초기화
	m_hDC = GetDC(m_hMainWnd);

	// 자주 사용하는 Pen 및 Brush 생성
	CreatePenBrush();

	// 별도의 비트맵을 윈도우와 동일한 해상도로 생성시킨다.
	m_hMemBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);

	// 생성시킨 비트맵을 목적지로 하는 DC 를 생성.
	m_hMemDC = CreateCompatibleDC(m_hDC);
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hMemDC, m_hMemBit);
	DeleteObject(hPrevBit);

	// Manager 초기화
	CTimeMgr::GetInst()->TimeMgrInit();
	CKeyMgr::GetInst()->KeyMgrInit();
	CLevelMgr::GetInst()->LevelMgrInit();
}

void CEngine::progress()
{
	CEngineTick();

	CEngineRender();
}


void CEngine::CEngineTick()
{
	CTimeMgr::GetInst()->TimeMgrTick();
	CKeyMgr::GetInst()->KeyMgrTick();
	CLevelMgr::GetInst()->LevelMgrTick();

}

void CEngine::CEngineRender()
{
	// 화면 클리어
	Rectangle(m_hMemDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// 레벨(스테이지) 렌더링
	CLevelMgr::GetInst()->LevelMgrRender(m_hMemDC);
	//CLevelMgr::GetInst()->LevelMgrRender(m_hDC);

	// MemBitmap -> MainWindowBitmap
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hMemDC, 0, 0, SRCCOPY);
}

void CEngine::CreatePenBrush()
{
	//// DC 펜 설정
	//HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	//HPEN hBlackPen = (HPEN)SelectObject(m_hDC, hRedPen);
	//DeleteObject(hBlackPen);

	//// DC 브러쉬 설정	
	//HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
	//HBRUSH hWhiteBrush = (HBRUSH)SelectObject(m_hDC, hBlueBrush);
	//DeleteObject(hWhiteBrush);
}
