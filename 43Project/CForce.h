#pragma once
#include "CObject.h"

class CForce :
    public CObject
{
private:
    float m_fAccTime;
    float m_fDuration;
    float m_fForceScale; // ���� ũ��
    float m_fForceRadius;  // ���� �ݰ�

public:
    void SetDuration(float _fDuration) { m_fDuration = _fDuration; }
    void SetForceScale(float _fScale) { m_fForceScale = _fScale; }
    void SetForceRadius(float _fRadius) { m_fForceRadius = _fRadius; }

public:
    void CForceTick();
    void CForceRender(HDC _dc); // �� override �� ���� ��

public:
    CForce();
    ~CForce();
};

