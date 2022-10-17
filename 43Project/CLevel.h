#pragma once
#include "CEntity.h"


class CObject;

class CLevel :
    public CEntity
{
private:
    vector<CObject*> m_arrLayer[(UINT)LAYER::END];

    UINT m_iTileXCount;
    UINT m_iTileYCount;
    // CreateTile() 에서 요구되는 타일 행, 열 개수

public:
    UINT GetTileXCount() { return m_iTileXCount; }
    UINT GetTileYCount() { return m_iTileYCount; }

public:
    virtual void LevelInit() = 0;
    virtual void LevelTick();
    virtual void Final_Tick();
    virtual void LevelRender(HDC _dc);

    virtual void LevelEnter() = 0; // 레벨에 진입할 때 호출 됨
    virtual void LevelExit() = 0; // 레벨을 벗어날 때 호출 됨



public:
    void AddObject(CObject* _pObj, LAYER _layer) 
    { 
        m_arrLayer[(UINT)_layer].push_back(_pObj);
    }

    const vector<CObject*>& GetLayer(LAYER _layer) { return m_arrLayer[(UINT)_layer];}

    void DeleteAllObject();

    void DeleteObject(LAYER _eLayer); // 기존의 브러쉬 등의 오브젝트 지우는 윈도우 함수하고 이름이 겹친다. 다음에는 이름을 바꾸자
    void CreateTile(UINT _X, UINT _Y);

public:
    CLONE_DEACTIVATE(CLevel);

public:
    CLevel();
    virtual ~CLevel();
};

