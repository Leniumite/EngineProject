#pragma once
#include "MeshComponent.h"
class TeapotMeshComponent :
    public MeshComponent
{
    LPD3DXMESH _teapotMesh;

public:

    TeapotMeshComponent(GameObject* gameObject);

    virtual void InitComponent() override;

    virtual void Draw() override;

    virtual void Update() override;

    virtual void Clean() override;

};

