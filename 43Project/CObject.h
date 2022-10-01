#pragma once
#include "CEntity.h"

class CCollider;

class CObject :
	public CEntity
{
private:
	Vec m_vPos;
	Vec m_vScale;

	CCollider* m_pCollider;

	bool m_bDead;

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

	virtual void CollisionBegin(CCollider* _pOther) {} // BeginOverlap
	virtual void Colliding(CCollider* _pOther) {} // OnOverlap
	virtual void CollisionEnd(CCollider* _pOther) {} // EndOverlap

public:
	bool IsDead() { return m_bDead; }
	void SetDead();
	void Instantiate(CObject* _pNewObj, Vec _vPos, LAYER _eLayer);

public:
	CObject();
	virtual ~CObject();

	friend class CEventMgr; // 이것으로 CEventMgr.cpp 에서 CObject* cobj 가 있다면 cobj->m_bDead 가 가능하다.
};

