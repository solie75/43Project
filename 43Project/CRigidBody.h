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

public:
    virtual void ComponentTick() override;
    virtual void Final_Tick() override;
    virtual void ComponentRender(HDC _dc) override;

public:
    void AddForce(Vec _vForce) { m_vForce += _vForce; }
    void SetVelocityLimit(float _fLimit) { m_fVelocityLimit = _fLimit; }
    void SetVelocity(Vec _vVelocity) { m_vVelocity = _vVelocity; }
    Vec GetVelocity() { return m_vVelocity; }
    void SetFriction(float _fFriction) { m_fFriction = _fFriction; }
    void SetFrictionScale(float _fFrictionScale) { m_fFrictionScale = _fFrictionScale; }
     
public:
    CRigidBody(CObject* _pOwner);
    virtual ~CRigidBody();
}; 

