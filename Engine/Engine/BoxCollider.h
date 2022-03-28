#pragma once
#include "Collider.h"
class BoxCollider :
    public Collider
{
private:

public:
    BoxCollider(GameObject* gameObject);
    virtual void InitComponent() override;
    D3DXVECTOR3 _posMin;
    D3DXVECTOR3 _posMax;
    D3DXVECTOR3 _center;

    D3DXVECTOR3 min = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
    D3DXVECTOR3 max = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

    float _distX;
    float _distY;
    float _distZ;

    virtual void Update() override;


};

