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
	if (_mesh != nullptr) {
		_mesh->Release();
		_mesh = NULL;
	}
}

