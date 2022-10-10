#include "pch.h"
#include "CForce.h"


CForce::CForce()
	: m_fAccTime(0.f)
	, m_fDuration(0.f)
	, m_fForceScale(0.f)
	, m_fForceRadius(0.f)
{
}

CForce::~CForce()
{
}

void CForce::CForceTick()
{
}

void CForce::CForceRender(HDC _dc)
{
}

