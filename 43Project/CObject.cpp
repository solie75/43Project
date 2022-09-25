#include "pch.h"
#include "CObject.h"

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

	/*Vec vPos = CObject::GetPos();
	Vec vScale = CObject::GetScale();*/
	
	/*Rectangle(_hdc,
		(int)(vPos.x - vScale.x / 2.f),
		(int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f),
		(int)(vPos.y + vScale.y / 2.f)
	);*/

}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider(this);
}