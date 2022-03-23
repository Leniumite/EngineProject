#include "pch.h"
#include "framework.h"

SphereMeshComponent::SphereMeshComponent(GameObject* gameObject) : MeshComponent(gameObject)
{
}


void SphereMeshComponent::InitComponent()
{
    D3DXCreateSphere(_d3ddev, .5f, 10, 10, &_mesh, NULL);
}

void SphereMeshComponent::Draw()
{
    MeshComponent::Draw();

    _d3ddev->SetFVF(CUSTOMFVF);

    _mesh->DrawSubset(0);
}

