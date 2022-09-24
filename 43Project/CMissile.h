#pragma once
#include "CObject.h"

class CMissile :
    public CObject
{
private:
    float m_fSpeed;
    float m_fDegree;

public:
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetDir(float _fDegree) { m_fDegree = _fDegree; }

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc) override;

public:
    CMissile();
    ~CMissile();
};

