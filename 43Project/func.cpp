#include "pch.h"
#include "func.h"

#include "CObject.h"

bool IsValid(CObject*& _pTarget)
{
    if (nullptr == _pTarget || _pTarget->IsDead())
    {
        _pTarget = nullptr;
        return false;
    }

    return true;
}
