#pragma once
#include "CEntity.h"

class CResource :
    public CEntity
{
private:
    wstring m_strKey; // 이름
    wstring m_strRelativePath; // 경로

public:
    const wstring& GetKey() { return m_strKey; }
    const wstring& GetRelativePath() { return m_strRelativePath; }

private:
    void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
    void SetRelativePath(const wstring& _strRelativepath) { m_strRelativePath = _strRelativepath; }

protected:
    virtual int Load(const wstring& _strFilePath) = 0;

public:
    CLONE_DEACTIVATE(CResource);

public:
    CResource();
    virtual ~CResource();

    friend class CResourceMgr; // 여기에서 왜 리소스 매니저가 frined class 로 지정되었는지 이유 파악할 것
    // CResourceMgr의 LoadTexture() 에서 Load()와 SetKey() SetRelativePath()에 접근하기 위해서
};

