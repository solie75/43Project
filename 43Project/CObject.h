#pragma once
#include "CEntity.h"

class CObject :
	public CEntity
{
private:
	Vec m_vPos;
	Vec m_vScale;

public:
	void SetPos(Vec _v) { m_vPos = _v; }
	Vec GetPos() { return m_vPos; }
	
	void SetScale(Vec _v) { m_vScale = _v; }
	Vec GetScale() { return m_vScale; }

public:
	virtual void ObjectTick();
	virtual void ObjectRender(HDC _hdc);

public:
	CObject();
	virtual ~CObject();
};

