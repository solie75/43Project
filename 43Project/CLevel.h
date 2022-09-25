#pragma once
#include "CEntity.h"
#include "CObject.h"

class CLevel :
    public CEntity
{
private:
    vector<CObject*> m_arrLayer[(UINT)LAYER::END];

public:
    virtual void LevelInit() = 0;
    virtual void LevelTick();
    virtual void LevelRender(HDC _dc);

public:
    void AddObject(CObject* _pObj, LAYER _layer) 
    { 
        m_arrLayer[(UINT)_layer].push_back(_pObj);
    }

public:
    CLevel();
    virtual ~CLevel();
};

