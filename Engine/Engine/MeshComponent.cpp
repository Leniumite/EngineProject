#include "pch.h"
#include "framework.h"

MeshComponent::MeshComponent(GameObject* gameObject) : Component(gameObject)
{
}

void MeshComponent::Clean()
{
}

void MeshComponent::Draw()
{
	_d3ddev->SetTransform(D3DTS_WORLD, &_gameObject->_transform->matrix);
}

