#include "pch.h"
#include "framework.h"

TorusMeshComponent::TorusMeshComponent(GameObject* gameObject) : MeshComponent(gameObject)
{
}

void TorusMeshComponent::InitComponent()
{
    D3DXCreateTorus(_d3ddev, 1.0f, 1.0f, 10, 3, &_torusMesh, NULL);
}

void TorusMeshComponent::Draw()
{
    MeshComponent::Draw();

    _d3ddev->SetFVF(CUSTOMFVF);

    _torusMesh->DrawSubset(0);
}

void TorusMeshComponent::Update()
{
}

void TorusMeshComponent::Clean()
{
    _torusMesh->Release();
}
