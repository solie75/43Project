#pragma once
#include "CObject.h"

class CMonster :
    public CObject
{
public:
    UINT m_iHP;
    CObject* m_pTarget;

private:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc) override;

    virtual void CollisionBegin(CCollider* _pOther) override;

public:
    void SetTarget(CObject* _pPlayer)
    {
        m_pTarget = _pPlayer;
    }

public:
    CMonster();
    ~CMonster();
};

