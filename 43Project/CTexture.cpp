#include "pch.h"
#include "CTexture.h"
#include "CEngine.h"

CTexture::CTexture()
    : m_hBit(nullptr)
    , m_hDC(nullptr)
    , m_tBitmapInfo {}
{
}

CTexture::~CTexture()
{
    DeleteObject(m_hBit);
    DeleteDC(m_hDC);
}

int CTexture::Load(const wstring& _strFilePath)
{
    // Bitmap 로딩
    m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);

    // Bitmap 과 연결 시킬 DC 생성
    m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
    HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
    DeleteObject(hPrevBit);

    return S_OK;
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
    // 별도의 비트맵을 윈도우와 동일한 해상도로 생성시킨다.
    m_hBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _iWidth, _iHeight);

    // 생성시킨 비트맴을 목적지로 하는 DC 생성
    m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());

    HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
    DeleteObject(hPrevBit);

    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);
}



