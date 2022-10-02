#include "pch.h"
#include "CObject.h"

#include "CEventMgr.h"

#include "CCollider.h"


CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
	, m_bDead(false)
{
}

CObject::~CObject()
{
	DEL(m_pCollider);
}


void CObject::ObjectTick()
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->ComponentTick();
	}
}

void CObject::ObjectRender(HDC _dc)
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->ComponentRender(_dc);
	}
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider(this);
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
