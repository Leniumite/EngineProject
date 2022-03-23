#include "pch.h"
#include "framework.h"

TeapotMeshComponent::TeapotMeshComponent(GameObject* gameObject) : MeshComponent(gameObject)
{
}

void TeapotMeshComponent::InitComponent()
{
    D3DXCreateTeapot(_d3ddev, &_mesh, NULL);
    ZeroMemory(&_material, sizeof(D3DMATERIAL9));
    _material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);   // set diffuse color to white
    _material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set ambient color to white
}

void TeapotMeshComponent::Draw()
{
    MeshComponent::Draw();

    _d3ddev->SetFVF(CUSTOMFVF);
    _d3ddev->SetMaterial(&_material);
    _mesh->DrawSubset(0);
}
