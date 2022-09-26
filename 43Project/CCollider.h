#pragma once
#include "CComponent.h"

class CCollider :
    public CComponent
{
private:
    Vec m_vOffsetPos;
    Vec m_vFinalPos;
    Vec m_vScale;

    int m_iOverlapCount;

public:
    void SetOffsetPos(Vec _vOffsetPos) { m_vOffsetPos = _vOffsetPos; }
    void SetScale(Vec _vScale) { m_vScale = _vScale; }

    Vec GetOffsetPos() { return m_vFinalPos; }
    Vec SetScale() { return m_vScale; }

public:
    virtual void ComponentTick();
    virtual void ComponentRender(HDC _dc);

public:
    void BeginOverlap(CCollider* _other);
    void EndOverlap(CCollider* _other);
    void onOverlap(CCollider* _other);

public:
    CCollider(CObject* _pOwner);
    ~CCollider();
};

