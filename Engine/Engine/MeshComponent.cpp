#include "pch.h"
#include "framework.h"

MeshComponent::MeshComponent(GameObject* gameObject) : Component(gameObject)
{
	_mesh = nullptr;
}

MeshComponent::~MeshComponent()
{
	Clean();
}

void MeshComponent::Clean()
{
	if (_mesh != NULL) {
		_mesh->Release();
		_mesh = NULL;
	}
}

void MeshComponent::Draw()
{
	_d3ddev->SetTransform(D3DTS_WORLD, &_gameObject->_transform->matrix);
}

