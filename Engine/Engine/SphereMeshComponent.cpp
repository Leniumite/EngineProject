#include "pch.h"
#include "framework.h"

SphereMeshComponent::SphereMeshComponent(GameObject* gameObject) : MeshComponent(gameObject)
{
}


void SphereMeshComponent::InitComponent()
{
    D3DXCreateSphere(_d3ddev, .5f, 10, 10, &_mesh, NULL);
    ZeroMemory(&_material, sizeof(D3DMATERIAL9));
    _material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);   // set diffuse color to white
    _material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set ambient color to white
}

void SphereMeshComponent::Draw()
{
    MeshComponent::Draw();

    _d3ddev->SetFVF(CUSTOMFVF);
    _d3ddev->SetMaterial(&_material);
    _mesh->DrawSubset(0);
}

