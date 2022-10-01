#include "pch.h"
#include "CObject.h"

#include "CEventMgr.h"

#include "CCollider.h"


CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
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

void CObject::ObjectRender(HDC _hdc)
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->ComponentRender(_hdc);
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