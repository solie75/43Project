#pragma once
#include "CLevel.h"


enum class EDITOR_MODE
{
    TILE,
    ANIMATION,
    OBJECT,

    NONE,
};

class CEditorLevel :
    public CLevel
{
private:
    EDITOR_MODE m_eMode;

public:
    virtual void LevelInit() override;
    virtual void LevelTick() override;
    virtual void LevelEnter() override;
    virtual void LevelExit() override;

public:
    virtual void Update();
    virtual void Tile_Update();
    virtual void Animation_Update();
    virtual void Object_Update();

public:
    void SaveTile();
    void LoadTile();

public:
    CEditorLevel();
    ~CEditorLevel();
};

