#pragma once
#include "Collider.h"
class SphereCollider :
    public Collider
{
private:
    D3DXVECTOR3 _center;
    float _r;
public:
    SphereCollider(GameObject* gameObject);
    virtual void InitComponent() override;
};

