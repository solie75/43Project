#pragma once
#include "CLevel.h"
class CStage01Level :
    public CLevel
{
public:
    virtual void LevelInit() override;

public:
    CStage01Level();
    ~CStage01Level();
};

