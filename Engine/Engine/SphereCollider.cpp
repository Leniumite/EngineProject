#include "pch.h"
#include "SphereCollider.h"

SphereCollider::SphereCollider(GameObject* gameObject) : Collider(gameObject)
{
}

void SphereCollider::InitComponent()
{
	meshComponent = _gameObject->GetComponent<MeshComponent>();
	if (meshComponent == NULL) {
		return;
	}
	LPD3DXMESH mesh = meshComponent->GetMesh();
	BYTE* vertex;
	int vertexByteSize = mesh->GetNumBytesPerVertex();
	int vertexCount = mesh->GetNumVertices();
	mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&vertex);



	for (size_t i = 0, offset = 0; i < vertexCount; i++)
	{
		D3DXVECTOR3 v;
		memcpy(&v, vertex + offset, 12);
		offset += vertexByteSize;

		if (v.x < min.x) {
			min.x = v.x;
		}
		if (v.y < min.y) {
			min.y = v.y;
		}
		if (v.z < min.z) {
			min.z = v.z;
		}
		if (v.x > max.x) {
			max.x = v.x;
		}
		if (v.y > max.y) {
			max.y = v.y;
		}
		if (v.z > max.z) {
			max.z = v.z;
		}
	}
	
	mesh->UnlockVertexBuffer();

	_center = ((min + max) / 2) + _gameObject->_transform->GetPosition();
	_d = max(max(abs(max.x- min.x),abs(min.y - max.y)), abs(min.z - max.z));

	
}

void SphereCollider::Update()
{
	_center = ((min + max) / 2) + _gameObject->_transform->GetPosition();
	_d = max(max(abs(max.x- min.x),abs(min.y - max.y)), abs(min.z - max.z));

}
