#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator(CObject* _pOwner)
	: CComponent(_pOwner) // ...? �̰� �𸣰ڳ�...
	, m_mapAnim {}
	, m_pCurAnim(nullptr)
	, m_bRepeat(false)
{
}

CAnimator::~CAnimator()
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin();
	for (; iter != m_mapAnim.end(); ++iter)
	{
		delete iter->second;
	}
}


void CAnimator::ComponentTick()
{
	if(nullptr == m_pCurAnim)
	{
		return;
	}

	if (m_pCurAnim->IsFinish() && m_bRepeat)
	{
		m_pCurAnim->Reset();
	}

	m_pCurAnim->AnimationTick();
}

void CAnimator::ComponentRender(HDC _dc)
{
	if (nullptr == m_pCurAnim)
	{
		return;
	}

	m_pCurAnim->AnimationRender(_dc);
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	CAnimation* pAnim = FindAnimation(_strName);
	if (nullptr == pAnim)
	{
		MessageBox(nullptr, L"�ش� Animation ����", L"Animation ��� ����", MB_OK);
		return;
	}

	m_pCurAnim = pAnim;
	m_pCurAnim->Reset(); // �ش� �ִϸ��̼��� �ʱ�ȭ�� ������.
	m_bRepeat = _bRepeat;
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pAtlas, Vec _vLeftTop, Vec _vSize, int _iMaxFrameCount, float _fDuration)
{
	CAnimation* pAnim = FindAnimation(_strName);
	assert(!pAnim); // ���� �ִϸ��̼��� ����� �� �̹� �����ϴ� ���̸� �ȵǱ� ������
	
	pAnim = new CAnimation(this);
	pAnim->AnimationInit(_strName, _pAtlas, _vLeftTop, _vSize, _iMaxFrameCount, _fDuration);
	m_mapAnim.insert(make_pair(_strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
	{
		return nullptr;
	}

	return iter->second;
}

CAnimation* CAnimator::LoadAnimation(const wstring& _strRelativePath)
{
	CAnimation* pAnim = new CAnimation(this);

	pAnim->Load(_strRelativePath);

	m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));

	return nullptr;
}

