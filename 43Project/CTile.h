#pragma once
#include "CObject.h"


class CTile :
    public CObject
{
private:
    CTexture* m_pAtlas; // 타일 이미지
    int m_iImgIdx;

public:
    void SetAtlas(CTexture* _pAtlas) { m_pAtlas = _pAtlas; }
    void SetImgIdx(int _imgidx);
    void AddImgIdx();

    virtual void ObjectTick() override;
    virtual void ObjectRender(HDC _dc) override;

    void TileSave(FILE* _pFile);
    void TileLoad(FILE* _pFile);

public:
    CLONE(CTile);

public:
    CTile();
    ~CTile();
};

