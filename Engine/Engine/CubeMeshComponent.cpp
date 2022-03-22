#include "pch.h"
#include "framework.h"

CubeMeshComponent::CubeMeshComponent(GameObject* gameObject) : MeshComponent(gameObject)
{
    _cubeMesh = nullptr;
}

void CubeMeshComponent::InitComponent()
{
    D3DXCreateBox(_d3ddev, 1.0f, 1.0f, 1.0f, &_cubeMesh, NULL);
}

void CubeMeshComponent::Draw()
{
    MeshComponent::Draw();

    _d3ddev->SetFVF(CUSTOMFVF);
    
    _cubeMesh->DrawSubset(0);
}

void CubeMeshComponent::Update()
{
    _gameObject->_transform->RotateYaw(8.0f * _engine->GetTimer()->deltaTime);
}

void CubeMeshComponent::Clean()
{
    //RELPTR(_cubeMesh);
    if (_cubeMesh)
    {
        _cubeMesh->Release();
        _cubeMesh = nullptr;
    }
}
