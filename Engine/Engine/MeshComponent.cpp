#include "pch.h"
#include "MeshComponent.h"

MeshComponent::MeshComponent(GameObject* gameObject) : Component(gameObject)
{
	_d3ddev = _engine->GetDevice();
}

