#include "pch.h"
#include "framework.h"

TorusMeshComponent::TorusMeshComponent(GameObject* gameObject) : MeshComponent(gameObject)
{
}

void TorusMeshComponent::InitComponent()
{
    D3DXCreateTorus(_d3ddev, 1.0f, 1.0f, 10, 3, &_mesh, NULL);
    ZeroMemory(&_material, sizeof(D3DMATERIAL9));
    _material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);   // set diffuse color to white
    _material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set ambient color to white
}

void TorusMeshComponent::Draw()
{
    MeshComponent::Draw();

    _d3ddev->SetFVF(CUSTOMFVF);
    _d3ddev->SetMaterial(&_material);
    _mesh->DrawSubset(0);
}

