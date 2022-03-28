#pragma once
#include "Collider.h"
class SphereCollider :
    public Collider
{
private:
    D3DXVECTOR3 min = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
    D3DXVECTOR3 max = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

public:
    SphereCollider(GameObject* gameObject);
    virtual void InitComponent() override;
    D3DXVECTOR3 _center;
    float _d;

    virtual void Update() override;


};

