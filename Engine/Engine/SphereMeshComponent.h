#pragma once
#include "MeshComponent.h"
class SphereMeshComponent :
    public MeshComponent
{
public:

    SphereMeshComponent(GameObject* gameObject);

    virtual void InitComponent() override;

    virtual void Draw() override;
};

