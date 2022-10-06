#include "pch.h"
#include "CAnimation.h"

#include "CTimeMgr.h"
#include "CCAmeraMgr.h"
#include "CPathMgr.h"
#include "CResourceMgr.h"

#include "CAnimator.h"
#include "CObject.h"
#include "CTexture.h"

CAnimation::CAnimation(CAnimator* _pAnimator)
	: m_pAnimator(_pAnimator) // ...?
	, m_vecFrame{}
	, m_pAtlas(nullptr)
	, m_iCurFrame(0)
	, m_fAccTime(0.f)
	, m_bFinish(false) // ...?
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::AnimationInit(const wstring& _strName, CTexture* _pAtlas, Vec _vLeftTop, Vec _vSize, int _iMaxFrameCount, float _fDuration)
{
	SetName(_strName); // Animation's name
	m_pAtlas = _pAtlas; // Animation's Atlas Image

	for (int i = 0; i < _iMaxFrameCount; ++i)
	{
		tAnimFrame frm = {};

		frm.vLeftTop = Vec(_vLeftTop.x + (float)i * _vSize.x, _vLeftTop.y);
		frm.vSize = _vSize;
		frm.fDuration = _fDuration;

		if (i == 4) // ...?
		{
			frm.vOffset = Vec(20.f, 0.f);
		}

		m_vecFrame.push_back(frm);
	}
}

void CAnimation::AnimationTick()
{
	if (m_bFinish)
	{
		return;
	}

	m_fAccTime += DT;
	
	if (m_vecFrame[m_iCurFrame].fDuration < m_fAccTime)
	{
		++m_iCurFrame;
		m_fAccTime = 0.f;

		if (m_vecFrame.size() <= m_iCurFrame)
		{
			m_iCurFrame = m_vecFrame.size() - 1;
			m_bFinish = true;
		}
	}
}

void CAnimation::AnimationRender(HDC _dc)
{
	CObject* pOwnerObject = m_pAnimator->GetOwner();
	Vec vPos = CCameraMgr::GetInst()->GetRenderPos(pOwnerObject->GetPos());

	tAnimFrame frm = m_vecFrame[m_iCurFrame];

	TransparentBlt(
		_dc,
		int(vPos.x - frm.vSize.x / 2.f),
		int(vPos.y - frm.vSize.y / 2.f),
		int(frm.vSize.x),
		int(frm.vSize.y),
		m_pAtlas->GetDC(),
		int(frm.vLeftTop.x),
		int(frm.vLeftTop.y),
		int(frm.vSize.x),
		int(frm.vSize.y),
		RGB(255, 0, 255)
	);
		
}

void CAnimation::Save(wstring& _strRelativePath )
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// ���� �����
	FILE* pFile = nullptr;
	errno_t iErrNum = _wfopen_s(&pFile, strFilePath.c_str(), L"wb"); 
	// �����ϸ� 0�� �����ϸ� �� �̿��� ������ ��ȯ�Ѵ�.
	// �����ϴ� �����ϴ� &pFile ���� ���� ��ϵ����� ���нÿ� pFile ���� NULL �� ����ȴ�.
	
	if (nullptr == pFile)
	{
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"Animation Save Fail, Error Number : %d", iErrNum);
		MessageBox(nullptr, szStr, L"���� ���� ����", MB_OK);
		return;
	}

	// Animation �̸� ����
	fwprintf_s(pFile, L"\n");

	fwprintf_s(pFile, L"[ANIMATION_NAME]\n");
	fwprintf_s(pFile, GetName().c_str());
	fwprintf_s(pFile, L"\n\n");

	// ��Ʋ�� �ؽ��� Ű�� ����	
	fwprintf_s(pFile, L"[ATLAS_KEY]\n");
	fwprintf_s(pFile, m_pAtlas->GetKey().c_str());
	fwprintf_s(pFile, L"\n\n");

	fwprintf_s(pFile, L"[ATLAS_PATH]\n");
	fwprintf_s(pFile, m_pAtlas->GetRelativePath().c_str());
	fwprintf_s(pFile, L"\n\n");

	// ������ ���� ����
	wchar_t szNum[50] = {}; // �ϳ��� �ִϸ��̼� ������ 50 �������� �ѱ� ��찡 ���ٰ� ����

	fwprintf_s(pFile, L"[FRAME_COUNT]\n");

	size_t iFrameCount = m_vecFrame.size();
	_itow_s((int)iFrameCount, szNum, 50, 10); // ������ ���ڿ��� ��ȯ

	fwprintf(pFile, szNum);
	fwprintf(pFile, L"\n\n");

	for (size_t i = 0; i < iFrameCount; ++i)
	{
		fwprintf(pFile, L"[%d_FRAME]\n", i);

		// LEFT_TOP
		fwprintf_s(pFile, L"[LEFT_TOP]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrame[i].vLeftTop.x, m_vecFrame[i].vLeftTop.y);

		// SIZE
		fwprintf_s(pFile, L"[SIZE]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrame[i].vSize.x, m_vecFrame[i].vSize.y);

		// OFFSET
		fwprintf_s(pFile, L"[OFFSET]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrame[i].vOffset.x, m_vecFrame[i].vOffset.y);

		// DURATION
		fwprintf_s(pFile, L"[DURATION]\n");
		fwprintf_s(pFile, L"%.2f\n", m_vecFrame[i].fDuration);

		fwprintf_s(pFile, L"\n");
	}
	
	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativePath)
{
	wstring strFilepath = CPathMgr::GetInst()->GetContentPath();
	strFilepath += _strRelativePath;

	// ���� �����
	FILE* pFile = nullptr;
	errno_t iErrNum = _wfopen_s(&pFile, strFilepath.c_str(), L"rb");

	if (nullptr == pFile)
	{
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"Animation Save ����, Error Number : %d", iErrNum);
		MessageBox(nullptr, szStr, L"���� ���� ����", MB_OK);
		return;
	}

	size_t iFrameCount = 0;
	wstring strAtlasKey;
	wstring strAtlasRelativePath;

	while (true)
	{
		wchar_t szBuffer[256] = {};
		fwscanf_s(pFile, L"%s", szBuffer, 256);

		if (!wcscmp(szBuffer, L"[ANIMATION_NAME]")) // szBuffer �� ����� ���ڿ��� "[ANIMATION_NAME]" ���
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			SetName(szBuffer);
		}
		else if (!wcscmp(szBuffer, L"[ATLAS_KEY]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			strAtlasKey = szBuffer;
		}
		else if (!wcscmp(szBuffer, L"[ATLAS_PATH]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			strAtlasRelativePath = szBuffer;
		}
		else if (!wcscmp(szBuffer, L"[FRAME_COUNT]"))
		{
			fwscanf_s(pFile, L"%zd", &iFrameCount);

			for (size_t i = 0; i < iFrameCount; ++i)
			{
				tAnimFrame frm = {};

				while (true)
				{
					wchar_t szBuffer[256] = {};
					fwscanf_s(pFile, L"%s", szBuffer, 256);

					wchar_t szBuffer[256] = {};
					fwscanf_s(pFile, L"%s", szBuffer, 256);

					if (!wcscmp(szBuffer, L"[LEFT_TOP]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.vLeftTop.x, &frm.vLeftTop.y);
					}

					else if (!wcscmp(szBuffer, L"[SIZE]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.vSize.x, &frm.vSize.y);
					}

					else if (!wcscmp(szBuffer, L"[OFFSET]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.vOffset.x, &frm.vOffset.y);
					}

					else if (!wcscmp(szBuffer, L"[DURATION]"))
					{
						fwscanf_s(pFile, L"%f", &frm.fDuration);
						break;
					}
				}

				m_vecFrame.push_back(frm);
			}

			break;
		}
	}

	m_pAtlas = CResourceMgr::GetInst()->LoadTexture(strAtlasKey, strAtlasRelativePath);

	fclose(pFile);
}