#include "pch.h"
#include "CEntity.h"

UINT CEntity::g_iNextID = 0;

CEntity::CEntity()
	: m_id(g_iNextID++) // ��� Entity �� �ٸ� ID �� ������ �ִ´�.
{
}

CEntity::CEntity(const CEntity& _Origin)
	: m_id(g_iNextID)
	, m_strName(_Origin.m_strName)
{
}

CEntity::~CEntity()
{
}
