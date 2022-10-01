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
				continue; // �浹�� �Ͼ� ���� ���� ���
			}
			// iRow ���̾�� iCal ���̾ ���� �浹 �˻縦 �����Ѵ�.
			CollisionBtwLayer((LAYER)iRow, (LAYER)iCol);
		}
	}
}

void CCollisionMgr::CollisionBtwLayer(LAYER _layer1, LAYER _layer2)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel(); // �� CLevelMgr���� GetCurLevel()�� �ٷ�ȣ�� �Ҽ� ���°� CLevelMgr::GetCurLevel() �� �ȵ�
	
	const vector<CObject*>& vecFirst = pCurLevel->GetLayer(_layer1);
	const vector<CObject*>& vecSecond = pCurLevel->GetLayer(_layer2);

	for (size_t i = 0; i < vecFirst.size(); ++i)
	{
		if (nullptr == vecFirst[i]->GetCollider())
		{
			continue;
		}

		size_t j = 0;
		if (_layer1 == _layer2) // Left, Right ���� ���̾��� ���, ���� �˻縦 ���ϱ� ����
		{
			j = i;
		}

		for (; j < vecSecond.size(); ++j)
		{
			if (nullptr == vecSecond[j]->GetCollider() || vecFirst[i] == vecSecond[j]) // �ٸ� ���̾ �����ϴ� �� ��ü�� ���� ���� �ֳ�?
			{
				continue;
			}

			// �� �浹ü�� ���̵� �����Ѵ�.
			CollisionID ID = {};
			ID.FirstID = vecFirst[i]->GetCollider()->GetID(); // ���⿡�� GetCollider �� �ִ� ������?
			ID.SecontID = vecSecond[j]->GetCollider()->GetID();

			// ���� �������� �浹�� Ȯ�� ( 
			map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);
			if (iter == m_mapPrevInfo.end())
			{
				m_mapPrevInfo.insert(make_pair(ID.id, false));
				iter = m_mapPrevInfo.find(ID.id);
			}

			bool bDead = vecFirst[i]->IsDead() || vecSecond[j]->IsDead();

			// ���� �浹 ������ ���
			if (CollisionBtwCollider(vecFirst[i]->GetCollider(), vecSecond[j]->GetCollider()))
			{
				// ���� �����ӿ��� �浹 ���� ���� ���
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

				// ���� �����ӿ� �浹 ���°� �ƴϾ���.
				else
				{
					if (!bDead) // �Ѵ� Dead ���°� �ƴ� ��� BiginOverlap �� �Ѵ�.
					{
						vecFirst[i]->GetCollider()->BeginOverlap(vecSecond[j]->GetCollider());
						vecSecond[j]->GetCollider()->BeginOverlap(vecFirst[i]->GetCollider());
						iter->second = true;
					}
				}
			}
			// ���� �浹���°� �ƴ� ���
			else
			{
				// ���� �����ӿ����� �浹 ���� ���� ���
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

