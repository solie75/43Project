#pragma once
#include "CLevel.h"
class CStartLevel :
    public CLevel
{
public:
    virtual void LevelInit() override;

public:
    CStartLevel();
    ~CStartLevel();
};

