#pragma once
#include "CEntity.h"

class CAnimator;
class CTexture;

class CAnimation :
    public CEntity
{
private:
    CAnimator* const    m_pAnimator;
    vector<tAnimFrame>  m_vecFrame;
    CTexture*           m_pAtlas;
    int                 m_iCurFrame;
    float               m_fAccTime; // Acceleration Time
    bool                m_bFinish;

private:
    void AnimationInit(
        const wstring& _strName,
        CTexture* _pAtlas,
        Vec _vLeftTop,
        Vec _vSize,
        int _iMaxFrameCount,
        float _fDuration);

public:
    void AnimationTick();
    void AnimationRender(HDC _dc);

public:
    bool IsFinish() { return m_bFinish; }
    void Reset()
    {
        m_bFinish = false;
        m_iCurFrame = 0;
        m_fAccTime = 0.f;
    }

    void Save(const wstring& _strRelativePath); // 상대 경로로 저장과 불러오기를 한다.
    void Load(const wstring& _strRelativePath);

public:
    CAnimation(CAnimator* _pAnimator);
    ~CAnimation();

    friend class CAnimator;
};

