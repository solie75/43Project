#include "pch.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"

class CObject;

CRigidBody::CRigidBody(CObject* _pOwner)
	: CComponent(_pOwner)
	, m_fMass(1.f)
	, m_fFriction(100.f)
	, m_fFrictionScale(1.f)
	, m_fVelocityLimit(10000.f)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::ComponentTick()
{
	// F = M * A
	// ���ӵ� ���ϱ�
	Vec cAccel = m_vForce / m_fMass;

	// ���ӵ��� �̿��ؼ� �ӵ��� ������Ų��.
	m_vVelocity += cAccel * DT;

	// ���� ���ӵ�
	Vec vFriction = -(m_vVelocity);
	if (!vFriction.IsZero()) // �ϳ��� �־��� ���� ���ؼ� �ְǹ� �� struct.h �� �����ص� ����̴�.
		// �������ӵ��� 0�� �ƴ� ���
	{
		vFriction.Normalize();
		vFriction *= (m_fFriction * m_fFrictionScale * m_fMass * DT); // ���� �̰� ������ �� �־��� ��
	}
	// ���� �ӵ� �ݴ� �������� ������ ���� �ӵ� ����
	m_vVelocity += vFriction;

	// �ӵ� ���ҷ�(�������� ����)�� ���� �ӵ��� �Ѿ ��� ���� ���η� �Ѵ�.
	if (m_vVelocity.ShiftingDistance() < vFriction.ShiftingDistance())
		// ���� �����ӿ� ��ü�� �־����� ��(�ӵ�) ���� �������� ������ ���� �� ũ�ٸ� ��ü�� �� �̻� �̵����� �ʴ´�.
		// Vec  �ڷ������� ���ϴ� �������� �� �����Ӵ� �̵��� �� �ִ� �Ÿ��� �Ǵ��Ѵ�.
	{
		m_vVelocity = Vec(0.f, 0.f);
	}
	
	// ������Ʈ�� ��ġ
	Vec vPos = GetOwner()->GetPos();
}

void CRigidBody::ComponentRender(HDC _dc)
{
}
