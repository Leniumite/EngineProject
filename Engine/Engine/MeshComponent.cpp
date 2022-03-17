#include "pch.h"
#include "MeshComponent.h"

MeshComponent::MeshComponent(GameObject* gameObject) : Component(gameObject)
{
	_d3ddev = _engine->GetDevice();
	InitMesh();
}

void MeshComponent::Draw()
{
	_d3ddev->SetTransform(D3DTS_WORLD, &_gameObject->_transform->matrix);
}

