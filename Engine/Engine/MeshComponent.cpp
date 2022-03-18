#include "pch.h"
#include "framework.h"

MeshComponent::MeshComponent(GameObject* gameObject) : Component(gameObject)
{
}

void MeshComponent::Clean()
{
	if (_vertexBuffer != NULL)
	{
		_vertexBuffer->Release();
	}
	if (_indexBuffer != NULL)
	{
		_indexBuffer->Release();
	}
	
}

void MeshComponent::Draw()
{
	_d3ddev->SetTransform(D3DTS_WORLD, &_gameObject->_transform->matrix);
}

