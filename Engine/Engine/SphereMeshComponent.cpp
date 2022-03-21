#include "pch.h"
#include "framework.h"

SphereMeshComponent::SphereMeshComponent(GameObject* gameObject) : MeshComponent(gameObject)
{
}


void SphereMeshComponent::InitComponent()
{
    D3DXCreateSphere(_d3ddev, .5f, 10, 10, &_sphereMesh, NULL);
}

void SphereMeshComponent::Draw()
{
    MeshComponent::Draw();

    _d3ddev->SetFVF(CUSTOMFVF);

    _sphereMesh->DrawSubset(0);
}

void SphereMeshComponent::Clean()
{
    _sphereMesh->Release();
}
