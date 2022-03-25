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

    float _distX;
    float _distY;
    float _distZ;



};

