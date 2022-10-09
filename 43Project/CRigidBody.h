#pragma once
#include "CComponent.h"

class CRigidBody :
    public CComponent
{
private:
    Vec m_vForce; // ��
    Vec m_vVelocity; // �ӵ�(vector)
    float m_fMass; // ����
    
    float m_fFriction; // ������
    float m_fFrictionScale; // �������

    float m_fVelocityLimit; // ���Ѽӵ�

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

