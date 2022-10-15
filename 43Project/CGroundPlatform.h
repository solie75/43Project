#pragma once
#include "CObject.h"
class CGroundPlatform :
    public CObject
{
public:
    virtual void CollisionBegin(CCollider* _pOther);
    virtual void Colliding(CCollider* _pOther);
    virtual void CollisionEnd(CCollider* _pOther);

public:
    CLONE(CGroundPlatform);

public:
    CGroundPlatform();
    ~CGroundPlatform();
};

