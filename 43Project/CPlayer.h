#pragma once
#include "CObject.h"

class CTexture;

class CPlayer :
    public CObject
{
private:
    float m_fSpeed;
    CTexture* m_pTexture;

public:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc) override;

    virtual void CollisionBegin(CCollider* _pOther) override;// BeginOverlap
    virtual void Colliding(CCollider* _pOther) override; // OnOverlap
    virtual void CollisionEnd(CCollider* _pOther) override; // EndOverlap

public:
    void SetSpeed(float _f)
    {
        m_fSpeed = _f;
    }

public:
    CPlayer();
    virtual ~CPlayer();
};

