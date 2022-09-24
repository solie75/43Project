#pragma once
#include "CObject.h"
class CPlayer :
    public CObject
{
private:
    float m_fSpeed;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc) override;

public:
    CPlayer();
    virtual ~CPlayer();
};

