#pragma once
#include "CEntity.h"

class CObject;

class CComponent :
    public CEntity
{
private:
    CObject* const m_pOwner;

public:
    virtual void ComponentTick() = 0;
    virtual void Final_Tick() {};
    virtual void ComponentRender(HDC _dc) = 0;

public:
    CObject* GetOwner() { return m_pOwner; }

public:
    CComponent(CObject* _pOwner);
    ~CComponent();
};

