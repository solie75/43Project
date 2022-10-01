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

    virtual void CollisionBegin(CCollider* _pOther) override;// BeginOverlap
    virtual void Colliding(CCollider* _pOther) override; // OnOverlap
    virtual void CollisionEnd(CCollider* _pOther) override; // EndOverlap

public:
    CPlayer();
    virtual ~CPlayer();
};

