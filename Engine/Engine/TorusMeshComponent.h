#pragma once

class TorusMeshComponent :
    public MeshComponent
{
    LPD3DXMESH _torusMesh;

public:

    TorusMeshComponent(GameObject* gameObject);

    virtual void InitComponent() override;

    virtual void Draw() override;

    virtual void Update() override;

    virtual void Clean() override;

};

