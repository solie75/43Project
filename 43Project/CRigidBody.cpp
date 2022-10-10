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
	// 가속도 구하기
	Vec cAccel = m_vForce / m_fMass;

	// 가속도를 이용해서 속도를 증가시킨다.
	m_vVelocity += cAccel * DT;

	// 마찰 가속도
	Vec vFriction = -m_vVelocity;
	if (!vFriction.IsZero()) // 하나의 주어진 값에 대해서 주건문 을 struct.h 에 선언해둔 경우이다.
		// 마찰가속도가 0이 아닌 경우
	{
		vFriction.Normalize(); // 여기에서 정규화를 하는 이유는? 방향!
		vFriction *= (m_fFriction * m_fFrictionScale * m_fMass * DT); // 내가 이걸 생각할 수 있었을 까
	}
	// 현재 속도 반대 방향으로 마찰에 의한 속도 감속
	m_vVelocity += vFriction;

	// 속도 감소량(마찰량에 의한)이 기존 속도를 넘어설 경우 완전 제로로 한다.
	if (m_vVelocity.ShiftingDistance() < vFriction.ShiftingDistance())
		// 현재 프레임에 객체에 주어지는 힘(속도) 보다 마찰력이 가지는 힘이 더 크다면 객체는 더 이상 이동하지 않는다.
		// Vec  자료형끼리 비교하는 수단으로 한 프레임당 이동할 수 있는 거리로 판단한다.
	{
		m_vVelocity = Vec(0.f, 0.f);
	}

	// 속도 제한 설정
	if (m_fVelocityLimit < m_vVelocity.ShiftingDistance())
	{
		// 제한 속도를 넘겼을 경우
		m_vVelocity.Normalize();
		m_vVelocity *= m_fVelocityLimit;
	}
	
	// 오브젝트의 위치
	Vec vPos = GetOwner()->GetPos();

	// 속도(속력 + 반향) 에 맞게 물체를 이동시킨다.
	// 위의 마찰력 단계를 거친 해당 프레임의 속도를 참고로 계산하여 위치를 정의 한다.
	vPos.x += m_vVelocity.x * DT;
	vPos.y += m_vVelocity.y * DT;

	GetOwner()->SetPos(vPos);

	// 키 입력이 IsPressed 이기 때문에 하나의 프레임안에서는 마지막에 힘을 초기화 해주고
	// 다음 프레임에서 키가 눌려있는지에 대한 여부로 힘에 대한 대입을 진행한다.
	m_vForce = Vec(0.f, 0.f);
}



void CRigidBody::ComponentRender(HDC _dc)
{
}
