#pragma once
#include "CObject.h"

class CForce :
    public CObject
{
private:
    float m_fAccTime;
    float m_fDuration;
    float m_fForceScale; // 힘의 크기
    float m_fForceRadius;  // 힘의 반경

public:
    void SetDuration(float _fDuration) { m_fDuration = _fDuration; }
    void SetForceScale(float _fScale) { m_fForceScale = _fScale; }
    void SetForceRadius(float _fRadius) { m_fForceRadius = _fRadius; }

public:
    void ObjectTick();
    void ObjectRender(HDC _dc); // 왜 override 가 없을 까

    CLONE(CForce);

public:
    CForce();
    ~CForce();
};

