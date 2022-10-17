#include "pch.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CPathMgr.h"
#include "CCameraMgr.h"
#include "CResourceMgr.h"

#include "CTexture.h"


CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_hDC(nullptr)
	//, m_hMemDC(nullptr)
	//, m_hMemBit(nullptr)
	, m_ptResolution{}
	, m_arrPen{}
	, m_pMemTex(nullptr)
{

}

CEngine::~CEngine()
{
	ReleaseDC(m_hMainWnd, m_hDC);
	//DeleteDC(m_hMemDC);
	//DeleteObject(m_hMemBit);

	for (UINT i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
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

	// 백버퍼 용 비트맵 제작
	m_pMemTex = CResourceMgr::GetInst()->CreateTexture(L"BeckBuffer", m_ptResolution.x, m_ptResolution.y);

	// 자주 사용하는 Pen 및 Brush 생성
	CreatePenBrush();

	//// 별도의 비트맵을 윈도우와 동일한 해상도로 생성시킨다.
	//m_hMemBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);

	// 생성시킨 비트맵을 목적지로 하는 DC 를 생성.
	//m_hMemDC = CreateCompatibleDC(m_hDC);
	//HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hMemDC, m_hMemBit);
	//DeleteObject(hPrevBit);

	// 별도의 비트맵을 만들고 그에 대한 DC 를 생성하는 것은 m_pMemTex 에서 한다.

	// Manager 초기화
	CPathMgr::GetInst()->PathMgrInit();
	CTimeMgr::GetInst()->TimeMgrInit();
	CKeyMgr::GetInst()->KeyMgrInit();
	CLevelMgr::GetInst()->LevelMgrInit();

}

void CEngine::progress()
{
	// 논리적 연산
	CEngineTick();

	// 화면 랜더링 갱신
	CEngineRender();

	// 다음 프레임에 적용될 이벤트 처리
	CEventMgr::GetInst()->EventMgrTick();
}


void CEngine::CEngineTick()
{
	// FPS, DeltaTime 계산
	CTimeMgr::GetInst()->TimeMgrTick();

	// Key Event 확인
	CKeyMgr::GetInst()->KeyMgrTick();

	// Camera
	CCameraMgr::GetInst()->CameraMgrTick();

	// 해당 Level 의 모든 객체 Tick 호출
	CLevelMgr::GetInst()->LevelMgrTick();

	// 모든 충돌체 호출
	CCollisionMgr::GetInst()->CollisionMgrTick();
}

void CEngine::CEngineRender()
{
	// 화면 클리어
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// 레벨(스테이지) 렌더링
	CLevelMgr::GetInst()->LevelMgrRender(m_pMemTex->GetDC());
	//CLevelMgr::GetInst()->LevelMgrRender(m_hDC);

	// Camera blind
	CCameraMgr::GetInst()->CameraMgrRender(m_pMemTex->GetDC());

	// MemBitmap -> MainWindowBitmap
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	// TimeMgr Rendering
	CTimeMgr::GetInst()->TimeMgrRender();
}

void CEngine::CreatePenBrush()
{

	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	//// DC 펜 설정
	//HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	//HPEN hBlackPen = (HPEN)SelectObject(m_hDC, hRedPen);
	//DeleteObject(hBlackPen);

	//// DC 브러쉬 설정	
	//HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
	//HBRUSH hWhiteBrush = (HBRUSH)SelectObject(m_hDC, hBlueBrush);
	//DeleteObject(hWhiteBrush);
}

void CEngine::ChangeWindowSize(UINT _iWidth, UINT _iHeight)
{
	m_ptResolution.x = _iWidth;
	m_ptResolution.y = _iHeight;

	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };

	HMENU hMenu = GetMenu(m_hMainWnd);

	if (nullptr != hMenu)
	{
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	}
	else
	{
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	}

	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// 백버퍼가 없으면 생성
	if (nullptr == m_pMemTex)
	{
		// 백버퍼용 비트맵 제장
		m_pMemTex = CResourceMgr::GetInst()->CreateTexture(L"BackBuffer", m_ptResolution.x, m_ptResolution.y);
	}

	// 백버퍼가 있으면, 변경된 해상도에 맞추어 크기 재조정
	else
	{
		m_pMemTex->ReSize(m_ptResolution.x, m_ptResolution.y);
	}
}