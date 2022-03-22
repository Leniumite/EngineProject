#pragma once

class TorusMeshComponent :
    public MeshComponent
{

public:

    TorusMeshComponent(GameObject* gameObject);

    virtual void InitComponent() override;

    virtual void Draw() override;

    virtual void Update() override;
};

