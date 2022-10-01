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


