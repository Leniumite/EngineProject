#pragma once
#include "Collider.h"
class BoxCollider :
    public Collider
{
private:
    D3DXVECTOR3 _posMin;
    D3DXVECTOR3 _posMax;
public:
    BoxCollider(GameObject* gameObject);
    virtual void InitComponent() override;

};

