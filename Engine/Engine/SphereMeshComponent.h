#pragma once
#include "MeshComponent.h"
class SphereMeshComponent :
    public MeshComponent
{
    LPD3DXMESH _sphereMesh;

public:

    SphereMeshComponent(GameObject* gameObject);

    virtual void InitComponent() override;

    virtual void Draw() override;

    virtual void Update() override;

    virtual void Clean() override;
};

