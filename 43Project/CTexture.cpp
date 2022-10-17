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
    // Bitmap �ε�
    m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);

    // Bitmap �� ���� ��ų DC ����
    m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
    HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
    DeleteObject(hPrevBit);

    return S_OK;
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
    // ������ ��Ʈ���� ������� ������ �ػ󵵷� ������Ų��.
    m_hBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _iWidth, _iHeight);

    // ������Ų ��Ʈ���� �������� �ϴ� DC ����
    m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());

    HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
    DeleteObject(hPrevBit);

    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);
}

void CTexture::ReSize(UINT _iWidth, UINT _iHeight)
{
    // ���ο� ��Ʈ�ʰ� ���ο� DC�� ����
    HBITMAP hNewBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _iWidth, _iHeight);
    HDC hNewDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
    HBITMAP hPrevBit = (HBITMAP)SelectObject(hNewDC, hNewBit);
    DeleteObject(hPrevBit);

    //  ������ �ִ� �׸��� ���ο� ������ �̻�
    BitBlt(hNewDC, 0, 0, m_tBitmapInfo.bmWidth, m_tBitmapInfo.bmHeight, m_hDC, 0, 0, SRCCOPY);

    // ���� ��Ʈ��, DC �� ����'
    DeleteObject(m_hBit);
    DeleteDC(hNewDC);

    // ���ο� ��Ʈ������ ���̵� ��ü
    m_hBit = hNewBit;
    m_hDC = hNewDC;

    // ��Ʈ�� ���� ����
    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);
}



