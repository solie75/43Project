#include "pch.h"
#include "CGroundPlatform.h"

#include "CCollider.h"
#include "CPlayer.h"
#include "CRigidBody.h"

CGroundPlatform::CGroundPlatform()
{
	CreateCollider();
	GetCollider()->SetScale(Vec(400.f, 50.f));
}

CGroundPlatform::~CGroundPlatform()
{

}

void CGroundPlatform::CollisionBegin(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr == pPlayer)
	{
		return;
	}
	pPlayer->GetRigidBody()->SetBoolOnGround(true);
}

void CGroundPlatform::Colliding(CCollider* _pOther)
{

}

void CGroundPlatform::CollisionEnd(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr == pPlayer)
	{
		return;
	}
	pPlayer->GetRigidBody()->SetBoolOnGround(false);
}

