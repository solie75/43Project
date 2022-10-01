#pragma once
#include "CEntity.h"
class CResource :
    public CEntity
{
private:
    wstring m_strKey; // �̸�
    wstring m_strRelativePath; // ���

public:
    const wstring& GetKey() { return m_strKey; }
    const wstring& GetRelativePath() { return m_strRelativePath; }

private:
    void Setkey(const wstring& _strKey) { m_strKey = _strKey; }
    void SetRelativePate(const wstring& _strRelativepath) { m_strRelativePath = _strRelativepath; }

protected:
    virtual int Load(const wstring& _strFilePath) = 0;

public:
    CResource();
    virtual ~CResource();

    friend class CResMgr; // ���⿡�� �� ���ҽ� �Ŵ����� frined class �� �����Ǿ����� ���� �ľ��� ��
};

