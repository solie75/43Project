#pragma once
#include "CComponent.h"

class CCollider :
    public CComponent
{
private:
    Vec m_vOffsetPos;
    Vec m_vFinalPos;
    Vec m_vScale;

public:
    void SetOffsetPos(Vec _vOffsetPos) { m_vOffsetPos = _vOffsetPos; }
    void SetScale(Vec _vScale) { m_vScale = _vScale; }

    Vec GetOffsetPos() { return m_vFinalPos; }
    Vec SetScale() { return m_vScale; }

public:
    virtual void ComponentTick();
    virtual void ComponentRender(HDC _dc);

public:
    CCollider(CObject* _pOwner);
    ~CCollider();
};

