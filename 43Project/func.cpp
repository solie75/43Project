#include "pch.h"
#include "func.h"

#include "CObject.h"

#include "CEventMgr.h"

bool IsValid(CObject*& _pTarget)
{
    if (nullptr == _pTarget || _pTarget->IsDead())
    {
        _pTarget = nullptr;
        return false;
    }

    return true;
}


void Instantiate(CObject* _pNewObj, Vec _vPos, LAYER _eLayer)
{
	_pNewObj->SetPos(_vPos);

	tEvent event = {};
	event.eType = EVENT_TYPE::CREATE_OBJECT;
	event.wPARAM = (DWORD_PTR)_pNewObj;
	event.lPARAM = (DWORD_PTR)_eLayer;

	CEventMgr::GetInst()->AddEvent(event);
}

void Saturate(float& _float)
{
	if (1.f < _float)
	{
		_float = 1.f;
	}	
	if (_float < 0.f)
	{
		_float = 0.f;
	}
}

void ChangeLevel(LEVEL_TYPE _eNextLevel)
{
	tEvent _event = {};
	_event.eType = EVENT_TYPE::LEVEL_CHANGE;
	_event.wPARAM = (DWORD_PTR)_eNextLevel;
	CEventMgr::GetInst()->AddEvent(_event);
}