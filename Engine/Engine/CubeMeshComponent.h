#pragma once

class CubeMeshComponent :
    public MeshComponent
{

    LPD3DXMESH _cubeMesh;

public:

    CubeMeshComponent(GameObject* gameObject);

    virtual ~CubeMeshComponent() override;

    virtual void InitComponent() override;

    virtual void Draw() override;

    virtual void Update() override;
    
    virtual void Clean() override;
};

