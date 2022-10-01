#pragma once
#include "CResource.h"
class CSound :
    public CResource
{
private:
    virtual int Load(const wstring& _strFilePath) override;

public:
    CSound();
    ~CSound();
};

