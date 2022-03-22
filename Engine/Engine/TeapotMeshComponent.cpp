#include "pch.h"
#include "framework.h"

TeapotMeshComponent::TeapotMeshComponent(GameObject* gameObject) : MeshComponent(gameObject)
{
}

void TeapotMeshComponent::InitComponent()
{
    D3DXCreateTeapot(_d3ddev, &_mesh, NULL);
}

void TeapotMeshComponent::Draw()
{
    MeshComponent::Draw();

    _d3ddev->SetFVF(CUSTOMFVF);

    _mesh->DrawSubset(0);
}

void TeapotMeshComponent::Update()
{
}
