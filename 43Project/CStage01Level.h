#pragma once
#include "CLevel.h"
class CStage01Level :
    public CLevel
{
public:
    virtual void LevelInit() override;
    virtual void LevelTick() override;

    virtual void LevelEnter() override;
    virtual void LevelExit() override;
public:
    CStage01Level();
    ~CStage01Level();
};

