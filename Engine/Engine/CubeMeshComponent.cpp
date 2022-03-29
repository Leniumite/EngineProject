#include "pch.h"
#include "framework.h"

CubeMeshComponent::CubeMeshComponent(GameObject* gameObject) : MeshComponent(gameObject)
{
    
}

void CubeMeshComponent::InitComponent()
{
    D3DXCreateBox(_d3ddev, 1.0f, 1.0f, 1.0f, &_mesh, NULL);
    ZeroMemory(&_material, sizeof(D3DMATERIAL9));
    _material.Diffuse = D3DXCOLOR(1.0f, .0f, .0f, 1.0f);   // set diffuse color to white
    _material.Ambient = D3DXCOLOR(1.0f, .0f, 0.0f, 1.0f);    // set ambient color to white
}

void CubeMeshComponent::Draw()
{
    _d3ddev->SetFVF(CUSTOMFVF);
    _d3ddev->SetMaterial(&_material);
    _mesh->DrawSubset(0);
}

void CubeMeshComponent::Update()
{
    _gameObject->_transform->RotateYaw(8.0f * _engine->GetTimer()->deltaTime);
}
