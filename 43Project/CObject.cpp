#include "pch.h"
#include "CObject.h"

#include "CEventMgr.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"


CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidBody(nullptr)
	, m_bDead(false)
{
}

CObject::~CObject()
{
	DEL(m_pCollider);
	DEL(m_pAnimator);
	DEL(m_pRigidBody);
}


void CObject::ObjectTick()
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->ComponentTick();
	}
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->ComponentTick();
	}
	if (nullptr != m_pRigidBody)
	{
		m_pRigidBody->ComponentTick();
	}
}

void CObject::Final_Tick()
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->Final_Tick();
	}
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->Final_Tick();
	}
	if (nullptr != m_pRigidBody)
	{
		m_pRigidBody->Final_Tick();
	}
}

void CObject::ObjectRender(HDC _dc)
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->ComponentRender(_dc);
	}
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->ComponentRender(_dc);
	}
	if (nullptr != m_pRigidBody)
	{
		m_pRigidBody->ComponentRender(_dc);
	}
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider(this);
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator(this);
}

void CObject::CreateRigidBody()
{
	m_pRigidBody = new CRigidBody(this);
}

void CObject::SetDead()
{
	tEvent event = {};
	event.eType = EVENT_TYPE::DELETE_OBJECT;
	event.wPARAM = (DWORD_PTR)this;
	CEventMgr::GetInst()->AddEvent(event);
}

void CObject::Instantiate(CObject* _pNewObj, Vec _vPos, LAYER _eLayer)
{
	_pNewObj->SetPos(_vPos);

	tEvent event = {};
	event.eType = EVENT_TYPE::CREATE_OBJECT;
	event.wPARAM = (DWORD_PTR)_pNewObj;
	event.lPARAM = (DWORD_PTR)_eLayer;

	CEventMgr::GetInst()->AddEvent(event);
}
