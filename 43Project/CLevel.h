#pragma once
#include "CEntity.h"
#include "CObject.h"

class CLevel :
    public CEntity
{
private:
    vector<CObject*> m_vecObject;

public:
    virtual void LevelInit() = 0;
    virtual void LevelTick();
    virtual void LevelRender(HDC _dc);

public:
    void AddObject(CObject* _pObj) { m_vecObject.push_back(_pObj); }

public:
    CLevel();
    virtual ~CLevel();
};

