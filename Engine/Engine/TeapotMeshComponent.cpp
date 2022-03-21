#include "pch.h"
#include "framework.h"

TeapotMeshComponent::TeapotMeshComponent(GameObject* gameObject) : MeshComponent(gameObject)
{
}

void TeapotMeshComponent::InitComponent()
{
    D3DXCreateTeapot(_d3ddev, &_teapotMesh, NULL);
}

void TeapotMeshComponent::Draw()
{
    MeshComponent::Draw();

    _d3ddev->SetFVF(CUSTOMFVF);

    _teapotMesh->DrawSubset(0);
}

void TeapotMeshComponent::Update()
{
}

void TeapotMeshComponent::Clean()
{
    _teapotMesh->Release();
}
