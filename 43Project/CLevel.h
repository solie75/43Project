#pragma once
#include "CEntity.h"


class CObject;

class CLevel :
    public CEntity
{
private:
    vector<CObject*> m_arrLayer[(UINT)LAYER::END];

public:
    virtual void LevelInit() = 0;
    virtual void LevelTick();
    virtual void Final_Tick();
    virtual void LevelRender(HDC _dc);

public:
    void AddObject(CObject* _pObj, LAYER _layer) 
    { 
        m_arrLayer[(UINT)_layer].push_back(_pObj);
    }

    const vector<CObject*>& GetLayer(LAYER _layer) { return m_arrLayer[(UINT)_layer];}

public:
    CLevel();
    virtual ~CLevel();
};

