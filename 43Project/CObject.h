#pragma once
#include "CEntity.h"

#include "CCollider.h"

class CObject :
	public CEntity
{
private:
	Vec m_vPos;
	Vec m_vScale;

	CCollider* m_pCollider;

public:
	void SetPos(Vec _v) { m_vPos = _v; }
	Vec GetPos() { return m_vPos; }
	
	void SetScale(Vec _v) { m_vScale = _v; }
	Vec GetScale() { return m_vScale; }

	void CreateCollider();

	CCollider* GetCollider() { return m_pCollider; }

public:
	virtual void ObjectTick();
	virtual void ObjectRender(HDC _hdc);

public:
	CObject();
	virtual ~CObject();
};

