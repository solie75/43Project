#pragma once
#include "CObject.h"
class CMonster :
    public CObject
{
public:

private:
    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc) override;

public:
    CMonster();
    ~CMonster();
};

