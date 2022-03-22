#include "pch.h"
#include "framework.h"

TorusMeshComponent::TorusMeshComponent(GameObject* gameObject) : MeshComponent(gameObject)
{
}

void TorusMeshComponent::InitComponent()
{
    D3DXCreateTorus(_d3ddev, 1.0f, 1.0f, 10, 3, &_mesh, NULL);
}

void TorusMeshComponent::Draw()
{
    MeshComponent::Draw();

    _d3ddev->SetFVF(CUSTOMFVF);

    _mesh->DrawSubset(0);
}

void TorusMeshComponent::Update()
{
}

void TorusMeshComponent::Clean()
{
    _mesh->Release();
}
