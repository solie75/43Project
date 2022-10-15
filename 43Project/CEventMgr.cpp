#include "pch.h"
#include "CEventMgr.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CObject.h"

CEventMgr::CEventMgr()
{}

CEventMgr::~CEventMgr()
{}

void CEventMgr::EventMgrTick()
{
	// 삭제 예정 오브젝트 관리
	for (size_t i = 0; i < m_vecGarbage.size(); ++i)
	{
		delete m_vecGarbage[i];
	}
	m_vecGarbage.clear();

	// 이벤트 처리
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		switch (m_vecEvent[i].eType)
		{
		case EVENT_TYPE::CREATE_OBJECT: // wParam : Object Adress, lParam : Layer
		{
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

			CObject* pNewObject = (CObject*)m_vecEvent[i].wPARAM;
			LAYER eLayer = (LAYER)m_vecEvent[i].lPARAM;

			pCurLevel->AddObject(pNewObject, eLayer);
		}
			break;
		case EVENT_TYPE::DELETE_OBJECT:
		{
			// 삭제 예정 오브젝트를 Dead 상태로 놓고 Garbage 에 넣는다.
			CObject* pObject = (CObject*)m_vecEvent[i].wPARAM;

			// 낮은 확률로 같은 tick에서 동시에 같은 오브젝트를 삭제 요청한 경우를 방어
			if (false == pObject->m_bDead)
			{
				m_vecGarbage.push_back(pObject);
				pObject->m_bDead = true;
			}
		}
			break;
		case EVENT_TYPE::LEVEL_CHANGE:
		{
			// wParam : Next Level Type
			LEVEL_TYPE eNextLevel = (LEVEL_TYPE)m_vecEvent[i].wPARAM;
			CLevelMgr::GetInst()->ChangeLevel(eNextLevel);
		}
			break;
		default:
			break;
		}
	}

	m_vecEvent.clear();
}
