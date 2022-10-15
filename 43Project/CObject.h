#pragma once
#include "CEntity.h"

class CCollider;
class CAnimator;
class CRigidBody;

class CObject :
	public CEntity
{
private:
	Vec m_vPos;
	Vec m_vScale;

	CCollider* m_pCollider;
	CAnimator* m_pAnimator;
	CRigidBody* m_pRigidBody;

	bool m_bDead;

public:
	void SetPos(Vec _v) { m_vPos = _v; }
	Vec GetPos() { return m_vPos; }
	
	void SetScale(Vec _v) { m_vScale = _v; }
	Vec GetScale() { return m_vScale; }

	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();

	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; }

public:
	virtual void ObjectTick();
	virtual void Final_Tick() final;
	virtual void ObjectRender(HDC _hdc);
	virtual void CollisionBegin(CCollider* _pOther) {} // BeginOverlap
	virtual void Colliding(CCollider* _pOther) {} // OnOverlap
	virtual void CollisionEnd(CCollider* _pOther) {} // EndOverlap

public:
	bool IsDead() { return m_bDead; }
	void SetDead();
	//void Instantiate(CObject* _pNewObj, Vec _vPos, LAYER _eLayer);

	virtual CObject* Clone() = 0;

public:
	CObject();
	CObject(const CObject& _other); 
	virtual ~CObject();

	friend class CEventMgr;
};

