#pragma once
#include "CComponent.h"

class CRigidBody :
    public CComponent
{
private:
    Vec m_vForce; // 힘
    Vec m_vVelocity; // 속도(vector)
    float m_fMass; // 질량
    
    float m_fFriction; // 마찰력
    float m_fFrictionScale; // 마찰계수

    float m_fVelocityLimit; // 제한속도
    float m_fGravityVLimit; // 중력에 의한 제한 속도

    float m_fGravityAccel; // 중력 가속도 설정
    bool m_bGravityUse; // 중력 사용여부
    bool m_bOnGround; // 땅위에 닿았는지 여부

public:
    virtual void ComponentTick() override;
    virtual void Final_Tick() override;
    virtual void ComponentRender(HDC _dc) override;

public:
    void AddForce(Vec _vForce) { m_vForce += _vForce; }
    void SetVelocityLimit(float _fLimit) { m_fVelocityLimit = _fLimit; }
    void SetGravityVelocityLimit(float _fLimit) { m_fGravityVLimit = _fLimit; }

    void SetVelocity(Vec _vVelocity) { m_vVelocity = _vVelocity; }
    Vec GetVelocity() { return m_vVelocity; }

    void SetFriction(float _fFriction) { m_fFriction = _fFriction; }
    void SetFrictionScale(float _fFrictionScale) { m_fFrictionScale = _fFrictionScale; }

    void AddVelocity(Vec _vAddV) { m_vVelocity += _vAddV; }

    void SetGravity(bool _bSet) { m_bGravityUse = _bSet; }
    void SetBoolOnGround(bool _bGround);
    void SetGravityAccel(float _fAccel) { m_fGravityAccel = _fAccel; }
     
public:
    CLONE(CRigidBody);

public:
    CRigidBody(CObject* _pOwner);
    CRigidBody(const CRigidBody& _other);
    virtual ~CRigidBody();
}; 

