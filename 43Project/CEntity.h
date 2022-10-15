#pragma once
class CEntity
{
private:
	static UINT g_iNextID; // CEntity 클라스가 새로 생성되어 생성자가 호출될때 마다 새로운 아이디를 부여하기 위해서

private:
	wstring m_strName;
	const UINT m_id;

public:
	void SetName(const wstring& _str) { m_strName = _str; }
	const wstring& GetName() { return m_strName; }
	UINT GetID() { return m_id; }

	virtual CEntity* Clone() = 0;

public:
	CEntity();
	CEntity(const CEntity& _Origin);
	~CEntity();
};

