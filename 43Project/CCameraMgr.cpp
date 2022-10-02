#include "pch.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CEngine.h"

CCameraMgr::CCameraMgr()
{}

CCameraMgr::~CCameraMgr()
{}

void CCameraMgr::CameraMgrTick()
{
	if (IsPressed(KEY::W))
		m_vLook.y -= 300.f * DT;
	if (IsPressed(KEY::S))
		m_vLook.y += 300.f * DT;
	if (IsPressed(KEY::A))
		m_vLook.x -= 300.f * DT;
	if (IsPressed(KEY::D))
		m_vLook.x += 300.f * DT;

	Vec vResolution = CEngine::GetInst()->GetResolution();
	vResolution /= 2.f;
	m_vDiff = m_vLook - vResolution;
}
