#pragma once
class CollisionManager
{
	vector<Collider*> _colliders;
	
public :
	void checkCollisions();
	bool SphereSphereCollision(SphereCollider* col1,SphereCollider* col2);
	bool BoxBoxCollision(BoxCollider* col1,BoxCollider* col2);
	bool BoxSphereCollision(BoxCollider* box, SphereCollider* sphere);

	void AddCollider(Collider* col);

	D3DXVECTOR3 Right = D3DXVECTOR3(1.f, 0.f, 0.f);
	D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.f, 0.f);
	D3DXVECTOR3 Forward = D3DXVECTOR3(0.f, 0.f, 1.f);
	bool hasCollide;


};

