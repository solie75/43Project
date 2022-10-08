#pragma once
#include "CLevel.h"
class CStartLevel :
    public CLevel
{
public:
    virtual void LevelInit() override;
    virtual void LevelTick() override;

public:
    CStartLevel();
    ~CStartLevel();
};

