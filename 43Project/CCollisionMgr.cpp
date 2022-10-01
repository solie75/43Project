#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevel.h"
#include "CLevelMgr.h"
#include "CObject.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_matrix{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::LayerCheck(LAYER _layer1, LAYER _layer2)
{
	UINT iRow = (UINT)_layer1;
	UINT iCol = (UINT)_layer2;

	if (iRow > iCol)
	{
		UINT iTemp = iCol;
		iCol = iRow;
		iRow = iTemp;
	}

	m_matrix[iRow] |= (1 << iCol);
}

void CCollisionMgr::CollisionMgrTick()
{
	for (UINT iRow = 0; iRow < (UINT)LAYER::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)LAYER::END; ++iCol)
		{
			if (!(m_matrix[iRow] & (1 << iCol))) 
			{
				continue; // 충돌이 일어 나지 않은 경우
			}
			// iRow 레이어와 iCal 레이어가 서로 충돌 검사를 진행한다.
			CollisionBtwLayer((LAYER)iRow, (LAYER)iCol);
		}
	}
}

void CCollisionMgr::CollisionBtwLayer(LAYER _layer1, LAYER _layer2)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel(); // 왜 CLevelMgr에서 GetCurLevel()을 바로호출 할수 없는가 CLevelMgr::GetCurLevel() 이 안됨
	
	const vector<CObject*>& vecFirst = pCurLevel->GetLayer(_layer1);
	const vector<CObject*>& vecSecond = pCurLevel->GetLayer(_layer2);

	for (size_t i = 0; i < vecFirst.size(); ++i)
	{
		if (nullptr == vecFirst[i]->GetCollider())
		{
			continue;
		}

		size_t j = 0;
		if (_layer1 == _layer2) // Left, Right 동일 레이어인 경우, 이중 검사를 피하기 위함
		{
			j = i;
		}

		for (; j < vecSecond.size(); ++j)
		{
			if (nullptr == vecSecond[j]->GetCollider() || vecFirst[i] == vecSecond[j]) // 다른 레이어에 존재하는 두 객체가 같을 수가 있나?
			{
				continue;
			}

			// 두 충돌체의 아이디를 조합한다.
			CollisionID ID = {};
			ID.FirstID = vecFirst[i]->GetCollider()->GetID(); // 여기에서 GetCollider 가 있는 이유는?
			ID.SecontID = vecSecond[j]->GetCollider()->GetID();

			// 이전 프레임의 충돌을 확인 ( 
			map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);
			if (iter == m_mapPrevInfo.end())
			{
				m_mapPrevInfo.insert(make_pair(ID.id, false));
				iter = m_mapPrevInfo.find(ID.id);
			}

			bool bDead = vecFirst[i]->IsDead() || vecSecond[j]->IsDead();

			// 지금 충돌 상태인 경우
			if (CollisionBtwCollider(vecFirst[i]->GetCollider(), vecSecond[j]->GetCollider()))
			{
				// 이전 프레임에도 충돌 상태 였던 경우
				if (iter->second)
				{
					if (bDead)
					{
						vecFirst[i]->GetCollider()->EndOverlap(vecSecond[j]->GetCollider());
						vecSecond[j]->GetCollider()->EndOverlap(vecFirst[i]->GetCollider());
					}
					else
					{
						vecFirst[i]->GetCollider()->OnOverlap(vecSecond[j]->GetCollider());
						vecSecond[j]->GetCollider()->OnOverlap(vecFirst[i]->GetCollider());
					}
				}

				// 이전 프레임에 충돌 상태가 아니었다.
				else
				{
					if (!bDead) // 둘다 Dead 상태가 아닌 경우 BiginOverlap 을 한다.
					{
						vecFirst[i]->GetCollider()->BeginOverlap(vecSecond[j]->GetCollider());
						vecSecond[j]->GetCollider()->BeginOverlap(vecFirst[i]->GetCollider());
						iter->second = true;
					}
				}
			}
			// 지금 충돌상태가 아닌 경우
			else
			{
				// 이전 프레임에서는 충돌 상태 였던 경우
				if (iter->second)
				{
					vecFirst[i]->GetCollider()->EndOverlap(vecSecond[j]->GetCollider());
					vecSecond[j]->GetCollider()->EndOverlap(vecFirst[i]->GetCollider());
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::CollisionBtwCollider(CCollider* _Collider1, CCollider* _Collider2)
{
	Vec vCollider1Pos = _Collider1->GetFinalPos();
	Vec vCollider1Scale = _Collider1->GetScale();

	Vec vCollider2Pos = _Collider2->GetFinalPos();
	Vec vCollider2Scale = _Collider2->GetScale();

	if (fabsf(vCollider1Pos.x - vCollider2Pos.x) > (vCollider1Scale.x / 2.f + vCollider2Scale.x / 2.f))
	{
		return false;
	}
	if (fabsf(vCollider1Pos.y - vCollider2Pos.y) > (vCollider1Scale.y / 2.f + vCollider2Scale.y / 2.f))
	{
		return false;
	}
	return true;
}

