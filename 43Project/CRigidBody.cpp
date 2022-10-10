#include "pch.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"
#include "CObject.h"

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
}

void CRigidBody::Final_Tick()
{
	// F = M * A
	// ���ӵ� ���ϱ�
	Vec cAccel = m_vForce / m_fMass;

	// ���ӵ��� �̿��ؼ� �ӵ��� ������Ų��.
	m_vVelocity += cAccel * DT;

	// ���� ���ӵ�
	Vec vFriction = -m_vVelocity;
	if (!vFriction.IsZero()) // �ϳ��� �־��� ���� ���ؼ� �ְǹ� �� struct.h �� �����ص� ����̴�.
		// �������ӵ��� 0�� �ƴ� ���
	{
		vFriction.Normalize(); // ���⿡�� ����ȭ�� �ϴ� ������? ����!
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

	// �ӵ� ���� ����
	if (m_fVelocityLimit < m_vVelocity.ShiftingDistance())
	{
		// ���� �ӵ��� �Ѱ��� ���
		m_vVelocity.Normalize();
		m_vVelocity *= m_fVelocityLimit;
	}
	
	// ������Ʈ�� ��ġ
	Vec vPos = GetOwner()->GetPos();

	// �ӵ�(�ӷ� + ����) �� �°� ��ü�� �̵���Ų��.
	// ���� ������ �ܰ踦 ��ģ �ش� �������� �ӵ��� ����� ����Ͽ� ��ġ�� ���� �Ѵ�.
	vPos.x += m_vVelocity.x * DT;
	vPos.y += m_vVelocity.y * DT;

	GetOwner()->SetPos(vPos);

	// Ű �Է��� IsPressed �̱� ������ �ϳ��� �����Ӿȿ����� �������� ���� �ʱ�ȭ ���ְ�
	// ���� �����ӿ��� Ű�� �����ִ����� ���� ���η� ���� ���� ������ �����Ѵ�.
	m_vForce = Vec(0.f, 0.f);
}



void CRigidBody::ComponentRender(HDC _dc)
{
}
