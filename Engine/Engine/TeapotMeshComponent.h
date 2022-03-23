#pragma once
#include "MeshComponent.h"
class TeapotMeshComponent :
    public MeshComponent
{
public:

    TeapotMeshComponent(GameObject* gameObject);

    virtual void InitComponent() override;

    virtual void Draw() override;

};

