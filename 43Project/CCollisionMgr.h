#pragma once

class CCollider;

union CollisionID
{
	struct
	{
		UINT FirstID;
		UINT SecontID;
	};

	UINT_PTR id;
};



class CCollisionMgr
{
	SINGLE(CCollisionMgr);

private:
	WORD					m_matrix[(UINT)LAYER::END];
	map<UINT_PTR, bool>		m_mapPrevInfo; //  map of Collisions <collision id, whether collider at last frame>

public:
	void LayerCheck(LAYER _layer1, LAYER _layer2);

	void Clear()
	{
		for (int i = 0; i < (UINT)LAYER::END; ++i)
		{
			m_matrix[i] = 0;
		}
	}

public:
	void CollisionMgrTick();

private:
	void CollisionBtwLayer(LAYER _layer1, LAYER _layer2);
	bool CollisionBtwCollider(CCollider* _Collider1, CCollider* _Collider2);
};

