#pragma once
#include "CObject.h"

class CMissile :
    public CObject
{
private:
    float m_fSpeed;
    float m_fDegree;

    float   m_fTime;

    CObject* m_pTargetObject;

public:
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetDir(float _fDegree) { m_fDegree = _fDegree; }

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc) override;

    virtual void CollisionBegin(CCollider* _pOther) override;

public:
    CMissile();
    ~CMissile();
};

