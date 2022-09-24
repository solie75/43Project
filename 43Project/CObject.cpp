#include "pch.h"
#include "CObject.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
{
}

CObject::~CObject()
{
}

void CObject::ObjectTick()
{

}

void CObject::ObjectRender(HDC _hdc)
{
	Vec vPos = CObject::GetPos();
	Vec vScale = CObject::GetScale();
	

	Rectangle(_hdc,
		(int)(vPos.x - vScale.x / 2.f),
		(int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f),
		(int)(vPos.y + vScale.y / 2.f)
	);

}

