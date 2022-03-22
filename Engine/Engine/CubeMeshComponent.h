#pragma once

class CubeMeshComponent :
    public MeshComponent
{

public:

    CubeMeshComponent(GameObject* gameObject);

    virtual void InitComponent() override;

    virtual void Draw() override;

    virtual void Update() override;
};

