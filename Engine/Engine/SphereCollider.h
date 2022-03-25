#pragma once
#include "Collider.h"
class SphereCollider :
    public Collider
{
private:

public:
    SphereCollider(GameObject* gameObject);
    virtual void InitComponent() override;
    D3DXVECTOR3 _center;
    float _d;
};

