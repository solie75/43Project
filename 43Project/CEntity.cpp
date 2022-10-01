#include "pch.h"
#include "CEntity.h"

UINT CEntity::g_iNextID = 0;

CEntity::CEntity()
	: m_id(g_iNextID++) // 모든 Entity 는 다른 ID 를 가지고 있는다.
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
